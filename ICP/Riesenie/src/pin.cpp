/**
 * @file pin.cpp
 * @author Richard Filo (xfilor00)
 * @brief Trieda pre pracu s grafickou reprezentaciou portu
 * @date 2021-05-06
 */

#include "pin.h"
//#include <QtGui>
#include "GraphicsBlock.h"
#include <QGraphicsScene>
#include <QInputDialog>


Pin::Pin( Block_schema *arg_schema, int index, bool output, QGraphicsItem* parent) : QGraphicsItem(parent), m_brush(Qt::darkGreen)
{
    setAcceptHoverEvents(true);
    obj_schema = arg_schema;
    this->index = index;
    this->output = output;
    GraphicsBlock* p;
    p = dynamic_cast<GraphicsBlock*>(parent);
    block_name = &(p->var_block_name);
}

QRectF Pin::boundingRect() const
{
    return QRectF(0,0,10,10);
}

void Pin::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    m_brush = Qt::green;
    update();
}

void Pin::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    m_brush = Qt::darkGreen;
    update();
}

void Pin::paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *)
{

    p->setBrush(m_brush);
    p->drawEllipse(0,0,10,10);
}

void Pin::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    static GraphicsBlock* p;
    static bool first_click = true;
    static std::string block1_name;
    static int index_output1;
    static QPointF pos1;
//    qDebug() << "Pin item clicked." << first_click << QString::fromStdString(*block_name) << index << output;
    if(first_click && output){
        block1_name = *block_name;
        index_output1 = index;
        pos1 = event->scenePos();
        first_click = false;
        p = dynamic_cast<GraphicsBlock*>(this->parentItem());
    }
    else if(!first_click && !output && !obj_schema->add_junction(block1_name,index_output1,*block_name,index)){
        first_click = true;
        QLineF line;
        line.setP1(pos1);
        line.setP2(event->scenePos());
        scene()->addLine(line);
        p->setFlags(p->flags().setFlag(QGraphicsItem::ItemIsMovable,false));
        p = dynamic_cast<GraphicsBlock*>(this->parentItem());
        p->setFlags(p->flags().setFlag(QGraphicsItem::ItemIsMovable,false));
    }
    else
        first_click = true;

}

void Pin::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    (void)event;    //warning unused parameter
    if(!output){
        std::string value;
        std::vector<int> port_value = obj_schema->get_block_inputs(*block_name)[index];

        if(port_value[0])
            value = std::to_string(port_value[1]);
        else
            value = "Undefined";

        bool ok;
        QString text = QInputDialog::getText(nullptr, "Block port", "value:", QLineEdit::Normal, QString::fromStdString(value) , &ok);
        if (ok && !text.isEmpty()){
            value = text.toStdString();
            int int_value;

            try {
                int_value = std::stoi(value);
            }
            catch (const std::invalid_argument& ia) {
                return;
            }
            obj_schema->set_block_input_by_index(int_value,*block_name,index);
        }
    }
}
