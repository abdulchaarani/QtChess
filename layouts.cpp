#include "layouts.hpp"

namespace layouts{
const QString menuButtonFont  = "QPushButton {"
                                        "  font-size: 20px;"
                                        "  font-family: Segoe UI Symbol;"
                                        "  font-weight: bold;"
                                        "  color: black;"
                                        "  height: 75px;"
                                        "  background-color: #80B7FF;"
                                        "  border-radius: 5px;"
                                        "  border: 1px solid black;"
                                        "  text-align: center;"
                                        "}";

const double offset{100.7};
const int marginX{10};
const int marginY{45};
const int pieceSize{60};
const int buttonSize{100};

const int boxSize{100};

const int labelSize{30};

const QFont pieceFont("Segoe UI Symbol", pieceSize);

const QString pieceStyle = "QPushButton{"
                      "  color: black;"
                      "  background-color: none;"
                      "  border-style: inset;"
                      "  }"
                      "QPushButton:pressed {"
                      "   border-style: inset;"
                      "}";

const QString checkedFont = "QPushButton{"
                  "  color: #F4CB16;"
                  "  background-color: none;"
                  "  border-style: inset;"
                  "  }"
                  "QPushButton:pressed {"
                  "   border-style: inset;"
                  "}";

const QString whiteTurnFont = "QLabel{"
                           "  background-color: white;"
                           "  color: black; "
                           " font-size: 20px;"
                           "  border-style: inset;"
                           "  }";

const QString blackTurnFont = "QLabel{"
                           "  background-color: black;"
                           "  color: white; "
                           " font-size: 20px;"
                           "  border-style: inset;"
                           "  }";

const QString whiteBoxFont = "QPushButton{"
                          "  background-color: rgb(238, 238, 212);"
                          "  border-style: inset;"
                          "  }"
                          "QPushButton:pressed {"
                          "   border-style: inset;"
                          "}";

const QString blackBoxFont = "QPushButton{"
                          "  background-color: rgb(126, 148, 90);"
                          "  border-style: inset;"
                          "  }"
                          "QPushButton:pressed {"
                          "   border-style: inset;"
                          "}";

const QString highlightKillFont = "QPushButton{"
                               "  background-color: #F90F33;"
                               "  border-style: solid;"
                               "  border-width: 2px;"
                               "  border-color: white;"
                               "  }"
                               "QPushButton:pressed {"
                               "   border-style: inset;"
                               "}";

const QString highlightMoveFont = "QPushButton{"
                               "  background-color: #0B76D4;"
                               "  border-style: solid;"
                               "  border-width: 2px;"
                               "  border-color: white;"
                               "  }"
                               "QPushButton:pressed {"
                               "   border-style: inset;"
                               "}";

}
