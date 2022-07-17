#include <QTextDocument>
#include <QTextCharFormat>
#include "WeightText.h"

WeightText::WeightText(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    this->weight = 1;
    weightDocument = new QTextDocument;


    QTextCharFormat charFormat;
    charFormat.setFont(QFont("Helvetica", 12));

    QPen outlinePen = QPen (QColor(200, 200, 200), 0.5, Qt::SolidLine);
    charFormat.setTextOutline(outlinePen);

    cursor = QTextCursor(weightDocument);
    cursor.setCharFormat(charFormat);
    cursor.insertText(QString::number(weight));


    this->setDocument(weightDocument);
    //this->setPlainText(QString::number(this->weight));
    this->setTextInteractionFlags(Qt::TextEditorInteraction);

    connect(this->document(), &QTextDocument::contentsChanged, this, &WeightText::setWeightFromText);
}

void WeightText::setWeight(int weight)
{
    this->weight = weight;
}

int WeightText::getWeight()
{
    return this->weight;
}

void WeightText::setWeightFromText()
{
    bool ok;

    int tempWeight = this->toPlainText().QString::toInt(&ok);

    if(ok) {
        setWeight(tempWeight);
    }
    else {
        this->setPlainText(QString::number(this->weight));
        //cursor.insertText(QString::number(this->weight));
    }
}
