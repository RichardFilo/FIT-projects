/**
 * @file pin.h
 * @author Richard Filo (xfilor00)
 * @brief Trieda pre pracu s grafickou reprezentaciou portu
 * @date 2021-05-06
 */

#ifndef PIN_H
#define PIN_H

#include <QGraphicsItem>
#include <QPainter>
#include "block_schema.h"

/**
 * @brief Trieda reprezentujuca graficku podobu portu
 */
class Pin : public QGraphicsItem
{
public:
    /**
     * @brief Skonstruuje objekt Pin
     * @param arg_schema ukazatel na blokovu schemu
     * @param index index portu
     * @param output urcuje ci ide o vystupny port
     * @param parent rodic(blok ktoremu patri tento pin)
     */
    Pin( Block_schema *arg_schema, int index, bool output, QGraphicsItem* parent = 0);

    /**
     * @brief Vracia plochu kam sa bude vykreslovat
     */
    QRectF boundingRect() const;

    /**
     * @brief Zmena farby pri vstupe mysi nad objekt
     */
    void hoverEnterEvent(QGraphicsSceneHoverEvent *);

    /**
     * @brief Zmena farby pri vystupe mysi prec z objektu
     */
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);

    /**
     * @brief Vypreslenie pinu
     */
    void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *);

    /**
     * @brief Vytvori spojenie
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief Ak ide o vstupny pin tak nastavy hodnotu
     */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);


private:
    /**
     * @brief obj_schema Ukazatel na blokovu schemu
     */
    Block_schema* obj_schema;

    /**
     * @brief m_brush farba pozadia
     */
    QBrush m_brush;

    /**
     * @brief index index portu
     */
    int index;

    /**
     * @brief block_name ukazatel na meno bloku ktoremu patri tento pin
     */
    std::string* block_name;

    /**
     * @brief output urcuje ci ide o vystupny port
     */
    bool output;
};

#endif // PIN_H
