/***************************************************************************
 *   Copyright 2021 Reion Wong <reion@cutefishos.com>                      *
 *   Copyright Ken <https://stackoverflow.com/users/1568857/ken>           *
 *   Copyright 2016 Leslie Zhai <xiangzhai83@gmail.com>                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

#include "shortcut.h"
#include "keyboardsearchmanager.h"

#include <QKeyEvent>

ShortCut::ShortCut(QObject *parent)
    : QObject(parent)
    , m_object(parent)
{
}

void ShortCut::install(QObject *target)
{
    // No need to remove, because memory space is automatically freed in qml.
    // if (m_object) {
    //     m_object->removeEventFilter(this);
    // }

    if (target) {
        target->installEventFilter(this);
        // m_object = target;
    }
}

bool ShortCut::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type() != QEvent::KeyPress) {
        return false;
    }

    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);

    switch (keyEvent->key()) {
        case (Qt::Key_F2): emit rename(); break;
        case (Qt::Key_Backspace): emit backspace(); break;
        case (Qt::Key_Delete): emit deleteFile(); break;
        case (Qt::Key_F5): emit refresh(); break;
    }

    if (keyEvent->modifiers() & Qt::ControlModifier) {
        switch (keyEvent->key()) {
            case (Qt::Key_C): emit copy(); break;
            case (Qt::Key_X): emit cut(); break;
            case (Qt::Key_W): emit close(); break;
            case (Qt::Key_P): emit paste(); break;
            case (Qt::Key_L): emit openPathEditor(); break;
            case (Qt::Key_H): emit showHidden(); break;
            case (Qt::Key_Z): emit undo(); break;
        }
    }

    if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return) {
        emit open();
    } else if (keyEvent->key() >= Qt::Key_A && keyEvent->key() <= Qt::Key_Z) {
        emit keyPressed(keyEvent->text());
        keyEvent->ignore();
    }

    return QObject::eventFilter(obj, e);

}
