/**
 * @file MessageLabel.cpp
 * @brief Fichier cpp de la classe MessageLabel
 */

#include "MessageLabel.h"



MessageLabel::MessageLabel(){
    this->setText("");
    this->setFixedHeight(30);
    this->setAlignment(Qt::AlignCenter);
    this->setStyleSheet("background-color: #24D26D; color: #334433; border-radius: 5px;");
    this->setVisible(false);
}


MessageLabel::MessageLabel(QString message, Style style, bool visibility){
    this->setText(message);
    this->setFixedHeight(30);
    this->setAlignment(Qt::AlignCenter);
    if(style==Red)
        this->setStyleSheet("background-color: #C8574D; color: #FFDFDF; border-radius: 5px;");
    if(style==Green)
        this->setStyleSheet("background-color: #24D26D; color: #334433; border-radius: 5px;");
    this->setVisible(visibility);
}

void MessageLabel::setProperty(QString message, Style style, bool visibility){
    this->setText(message);
    if(style==NoStyle)
        this->setStyleSheet("");
    if(style==Red)
        this->setStyleSheet("background-color: #C8574D; color: #FFDFDF; border-radius: 5px;");
    if(style==Green)
        this->setStyleSheet("background-color: #24D26D; color: #334433; border-radius: 5px;");
    this->setVisible(visibility);
}
