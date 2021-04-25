#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

bool init_camera_settings() {
  camera_config_t config;

  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_QVGA;
  config.jpeg_quality = 10;
  config.fb_count = 1;

  esp_err_t result = esp_camera_init(&config);
  return result == ESP_OK;
}

mtmn_config_t mtmn_config;

static inline mtmn_config_t app_mtmn_config()
{
  mtmn_config_t mtmn_config = {0};
  mtmn_config.type = FAST;
  mtmn_config.min_face = 80;
  mtmn_config.pyramid = 0.707;
  mtmn_config.pyramid_times = 4;
  mtmn_config.p_threshold.score = 0.6;
  mtmn_config.p_threshold.nms = 0.7;
  mtmn_config.p_threshold.candidate_number = 20;
  mtmn_config.r_threshold.score = 0.7;
  mtmn_config.r_threshold.nms = 0.7;
  mtmn_config.r_threshold.candidate_number = 10;
  mtmn_config.o_threshold.score = 0.7;
  mtmn_config.o_threshold.nms = 0.7;
  mtmn_config.o_threshold.candidate_number = 1;
  return mtmn_config;
}

void initialize_camera() {
  if (!init_camera_settings()) {
    return;
  }

  mtmn_config = app_mtmn_config();
}


int pixel_to_degree(int distance) {
  return (int)(distance / 8);
}

void draw_face_boxes(dl_matrix3du_t *image_matrix, box_array_t *boxes) {
  int x, y, h_w, h_h;
  int img_center_x, img_center_y;

  img_center_x = (int)(image_matrix->w / 2);
  img_center_y = (int)(image_matrix->h / 2);

  for (int i = 0; i < boxes->len; i++) {
    //do {
    x = ((int)boxes->box[i].box_p[0]);
    h_w = ((int)boxes->box[i].box_p[2] - x + 1) / 2;

    y = ((int)boxes->box[i].box_p[1]);
    h_h = ((int)boxes->box[i].box_p[3] - y + 1) / 2;

    int face_center_x = x + h_w;
    int face_center_y = y + h_h;

    int x_distance = img_center_x - face_center_x;    // if < 0, movement toward right. If > 0, movement toward left.
    int y_distance = img_center_y - face_center_y;    // if < 0, movement toward down. If > 0, movement toward up.

    pan_position += pixel_to_degree(x_distance);
    tilt_position -= pixel_to_degree(y_distance);

    ledcAnalogWrite(pan_ch, pan_position);
    delay(100);
    ledcAnalogWrite(tilt_ch, tilt_position);
    delay(100);


    // Serial.printf("(face_center_x, face_center_y), (img_center_x, img_center_y)\n");
    // Serial.printf("(%d, %d), (%d, %d)\n", face_center_x, face_center_y, img_center_x, img_center_y);
  }
}

int face_tracking() {
  int count = 0;
  long distance;
  bool exit = false;
  String data;
  String msg;

  if (phase == 1) {
    msg = END_SPEAK_1;
  }
  else {
    msg = END_SPEAK_2;
  }

  do {
    data = serial_read();
    if (data.length() > 0 && data == msg) {
      exit = true;
      return 1;
    }

    if (data.length() > 0 && data == START_GAME) {
      exit = true;
      return 2;
    }

    camera_fb_t * frame;
    frame = esp_camera_fb_get();

    dl_matrix3du_t *image_matrix = dl_matrix3du_alloc(1, frame->width, frame->height, 3);
    fmt2rgb888(frame->buf, frame->len, frame->format, image_matrix->item);
    esp_camera_fb_return(frame);
    box_array_t *boxes = face_detect(image_matrix, &mtmn_config);

    distance = get_distance();

    if ((distance < SOGLIA_DIST && distance > 0) || boxes != NULL) {
      count = 0;
    }
    else {
      count++;
    }

    if (boxes != NULL) {
      draw_face_boxes(image_matrix, boxes);
      dl_lib_free(boxes->score);
      dl_lib_free(boxes->box);
      dl_lib_free(boxes->landmark);
      dl_lib_free(boxes);
    }

    dl_matrix3du_free(image_matrix);
    delay(150);

  } while (count < MAX_ERROR && !exit);

  return 0;
}
