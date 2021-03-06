/**
 ******************************************************************************
 *
 * @file       reloadpromptutils.cpp
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 *             Parts by Nokia Corporation (qt-info@nokia.com) Copyright (C) 2009.
 * @brief      
 * @see        The GNU Public License (GPL) Version 3
 * @defgroup   
 * @{
 * 
 *****************************************************************************/
/* 
 * This program is free software; you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation; either version 3 of the License, or 
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License 
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with this program; if not, write to the Free Software Foundation, Inc., 
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "reloadpromptutils.h"

#include <QtWidgets/QMessageBox>
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>

using namespace Utils;

QTCREATOR_UTILS_EXPORT Utils::ReloadPromptAnswer
    Utils::reloadPrompt(const QString &fileName, bool modified, QWidget *parent)
{

    const QString title = QCoreApplication::translate("Utils::reloadPrompt", "File Changed");
    QString msg;

    if (modified)
        msg = QCoreApplication::translate("Utils::reloadPrompt",
                                          "The unsaved file %1 has been changed outside Qt Creator. Do you want to reload it and discard your changes?").arg(QDir::toNativeSeparators(fileName));
    else
        msg = QCoreApplication::translate("Utils::reloadPrompt",
                                          "The file %1 has changed outside Qt Creator. Do you want to reload it?").arg(QDir::toNativeSeparators(fileName));
    return reloadPrompt(title, msg, parent);
}

QTCREATOR_UTILS_EXPORT Utils::ReloadPromptAnswer
    Utils::reloadPrompt(const QString &title, const QString &prompt, QWidget *parent)
{
    switch (QMessageBox::question(parent, title, prompt,
                                  QMessageBox::Yes|QMessageBox::YesToAll|QMessageBox::No|QMessageBox::NoToAll,
                                  QMessageBox::YesToAll)) {
    case QMessageBox::Yes:
        return  ReloadCurrent;
    case QMessageBox::YesToAll:
        return ReloadAll;
    case QMessageBox::No:
        return ReloadSkipCurrent;
    default:
        break;
    }
    return ReloadNone;
}
