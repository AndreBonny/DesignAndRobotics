String sendFinalResults(int num_correct, int num_questions) {
  int num_wrong = num_questions - num_correct;

  int perc_corr = (int)(num_correct * 100) / num_questions;
  int perc_wrong = (int)(num_wrong * 100) / num_questions;

  String ptr = "";
  ptr += "<!DOCTYPE html>";
  ptr += "<html>";
  ptr += "    <head>";
  ptr += "        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\", user-scalable=no>";
  ptr += "        <title>Results page</title>";
  ptr += "        <link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">";
  ptr += "    </head>";
  ptr += "    <body>";
  ptr += "        <img class=\"background\" src=\"/background.jpg\"/>";
  ptr += "        <main>";
  ptr += "            <div class=\"cover-disconnect\">";
  ptr += "            </div>";
  ptr += "            <div class=\"cover cover-header\">";
  ptr += "                <h2>Your score</h2>";
  ptr += "            </div>";
  ptr += "            <div class=\"cover cover-main\">";
  ptr += "                <div class=\"cover__text-blur\">";
  ptr += "                    <div class=\"score\">";
  ptr += "                        <h5>Wrong</h5>";
  ptr += "                        <div class=\"bar\">";
  if (perc_wrong != 0)
    ptr += "                            <div class=\"wrong wrong-" + String(perc_wrong) + "\"><h3>" + String(num_wrong) + "</h4></div>";
  if (perc_corr != 0)
    ptr += "                            <div class=\"correct corr-" + String(perc_corr) + "\"><h3>" + String(num_correct) + "</h4></div>";
  ptr += "                        </div>";
  ptr += "                        <h5>Correct</h5>";
  ptr += "                    </div>";
  ptr += "                </div>";
  ptr += "            </div>";
  ptr += "            <div class=\"cover cover-footer\">";
  ptr += "                <a href=\"/disconnect\" class=\"button\">Exit</a>";
  ptr += "            </div>";
  ptr += "        </main>";
  ptr += "    </body>";
  ptr += "    <script type=\"text/javascript\">";
  ptr += "        if(window.innerHeight <= 600) {";
  ptr += "            let ps = document.getElementsByTagName(\"p\");";
  ptr += "            for(i=0; i<ps.length; i++) {";
  ptr += "                ps[i].style.fontSize = \"10px\";";
  ptr += "            }";
  ptr += "            let h4s = document.getElementsByTagName(\"h4\");";
  ptr += "            for(i=0; i<h4s.length; i++) {";
  ptr += "                h4s[i].style.fontSize = \"15px\";";
  ptr += "            }";
  ptr += "            let h5s = document.getElementsByTagName(\"h5\");";
  ptr += "            for(i=0; i<h5s.length; i++) {";
  ptr += "                h5s[i].style.fontSize = \"13px\";";
  ptr += "            }";
  ptr += "            let h3s = document.getElementsByTagName(\"h3\");";
  ptr += "            for(i=0; i<h3s.length; i++) {";
  ptr += "                h3s[i].style.fontSize = \"13px\";";
  ptr += "            }";
  ptr += "            let scores = document.getElementsByClassName(\"score\");";
  ptr += "            for(i=0; i<scores.length; i++) {";
  ptr += "                scores[i].style.height = \"80%\";";
  ptr += "            }";
  ptr += "        }";
  ptr += "        if(window.innerHeight >= 1000) {";
  ptr += "            let ps = document.getElementsByTagName(\"p\");";
  ptr += "            for(i=0; i<ps.length; i++) {";
  ptr += "                ps[i].style.fontSize = \"30px\";";
  ptr += "            }";
  ptr += "            let h4s = document.getElementsByTagName(\"h4\");";
  ptr += "            for(i=0; i<h4s.length; i++) {";
  ptr += "                h4s[i].style.fontSize = \"45px\";";
  ptr += "            }";
  ptr += "            let h3s = document.getElementsByTagName(\"h3\");";
  ptr += "            for(i=0; i<h3s.length; i++) {";
  ptr += "                h3s[i].style.fontSize = \"40px\";";
  ptr += "            }";
  ptr += "            let h5s = document.getElementsByTagName(\"h5\");";
  ptr += "            for(i=0; i<h5s.length; i++) {";
  ptr += "                h5s[i].style.fontSize = \"40px\";";
  ptr += "            }";
  ptr += "        }";
  ptr += "    </script>";
  ptr += "</html>";

  return ptr;

}

String sendPResults(int quest_num, String result) {
  String ptr = "";
  ptr += "<!DOCTYPE html>";
  ptr += "<html>";
  ptr += "    <head>";
  ptr += "        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\", user-scalable=no>";
  ptr += "        <title>Welcome page</title>";
  ptr += "        <link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">";
  ptr += "    </head>";
  ptr += "    <body>";
  ptr += "        <img class=\"background\" src=\"/background.jpg\"/>";
  ptr += "        <main>";
  ptr += "            <div class=\"cover-disconnect\">";
  ptr += "                <a href=\"/disconnect\" class=\"disconnect\"> Disconnect </a>";
  ptr += "            </div>";
  ptr += "            <div class=\"cover cover-header\">";
  ptr += "                <h2>" + String(quest_num) + ". Question</h3>";
  ptr += "            </div>";
  ptr += "            <div class=\"cover cover-main\">";
  ptr += "                <div class=\"cover__text-blur\">";
  ptr += "                    <div class=\"cover__text\">";
  ptr += "                        <h4>" + result + "</h4>";
  ptr += "                    </div>";
  ptr += "                </div>";
  ptr += "            </div>";
  ptr += "            <div class=\"cover cover-footer\">";
  ptr += "                <a href=\"/question\" class=\"button btn-next\"> Next </a>";
  ptr += "            </div>";
  ptr += "        </main>";
  ptr += "    </body>";
  ptr += "    <script type=\"text/javascript\">";
  ptr += "        if(window.innerHeight <= 600) {";
  ptr += "            let ps = document.getElementsByTagName(\"p\");";
  ptr += "            for(i=0; i<ps.length; i++) {";
  ptr += "                ps[i].style.fontSize = \"10px\";";
  ptr += "            }";
  ptr += "            let hs = document.getElementsByTagName(\"h4\");";
  ptr += "            for(i=0; i<hs.length; i++) {";
  ptr += "                hs[i].style.fontSize = \"15px\";";
  ptr += "            }";
  ptr += "        }";
  ptr += "        if(window.innerHeight >= 1000) {";
  ptr += "            let ps = document.getElementsByTagName(\"p\");";
  ptr += "            for(i=0; i<ps.length; i++) {";
  ptr += "                ps[i].style.fontSize = \"30px\";";
  ptr += "            }";
  ptr += "            let hs = document.getElementsByTagName(\"h4\");";
  ptr += "            for(i=0; i<hs.length; i++) {";
  ptr += "                hs[i].style.fontSize = \"45px\";";
  ptr += "            }";
  ptr += "        }";
  ptr += "        document.getElementsByClassName(\"btn-next\")[0].style.visibility = \"hidden\";";
  ptr += "        setTimeout(function() {";
  ptr += "          document.getElementsByClassName(\"btn-next\")[0].style.visibility = \"visible\";";
  ptr += "        }, 2000);";
  ptr += "    </script>";
  ptr += "</html>";

  return ptr;

}

String sendQuestionPage(int quest_num, String question) {
  String ptr = "";
  ptr += "<!DOCTYPE html>";
  ptr += "<html>";
  ptr += "    <head>";
  ptr += "        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\", user-scalable=no>";
  ptr += "        <title>Question " + String(quest_num) + "</title>";
  ptr += "        <link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">";
  ptr += "    </head>";
  ptr += "    <body>";
  ptr += "        <img class=\"background\" src=\"/background.jpg\"/>";
  ptr += "        <main>";
  ptr += "            <div class=\"cover-disconnect\">";
  ptr += "                <a href=\"/disconnect\" class=\"disconnect\"> Disconnect </a>";
  ptr += "            </div>";
  ptr += "            <div class=\"cover cover-header\">";
  ptr += "                <h2>" + String(quest_num) + ". Question</h3>";
  ptr += "            </div>";
  ptr += "            <div class=\"cover cover-main\">";
  ptr += "                <div class=\"cover__text-blur\">";
  ptr += "                    <div class=\"cover__text\">";
  ptr += "                        <h4>" + question + "</h4>";
  ptr += "                    </div>";
  ptr += "                </div>";
  ptr += "            </div>";
  ptr += "            <div class=\"cover cover-footer\">";
  ptr += "                <a href=\"/false\" class=\"button\"> False </a>";
  ptr += "                <a href=\"/true\" class=\"button\"> True </a>";
  ptr += "            </div>";
  ptr += "        </main>";
  ptr += "    </body>";
  ptr += "    <script type=\"text/javascript\">";
  ptr += "        if(window.innerHeight <= 600) {";
  ptr += "            let ps = document.getElementsByTagName(\"p\");";
  ptr += "            for(i=0; i<ps.length; i++) {";
  ptr += "                ps[i].style.fontSize = \"10px\";";
  ptr += "            }";
  ptr += "            let hs = document.getElementsByTagName(\"h4\");";
  ptr += "            for(i=0; i<hs.length; i++) {";
  ptr += "                hs[i].style.fontSize = \"15px\";";
  ptr += "            }";
  ptr += "        }";
  ptr += "        if(window.innerHeight >= 1000) {";
  ptr += "            let ps = document.getElementsByTagName(\"p\");";
  ptr += "            for(i=0; i<ps.length; i++) {";
  ptr += "                ps[i].style.fontSize = \"30px\";";
  ptr += "            }";
  ptr += "            let hs = document.getElementsByTagName(\"h4\");";
  ptr += "            for(i=0; i<hs.length; i++) {";
  ptr += "                hs[i].style.fontSize = \"45px\";";
  ptr += "            }";
  ptr += "        }";
  ptr += "    </script>";
  ptr += "</html>";

  return ptr;
}
