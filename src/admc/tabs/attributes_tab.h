/*
 * ADMC - AD Management Center
 *
 * Copyright (C) 2020 BaseALT Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ATTRIBUTES_TAB_H
#define ATTRIBUTES_TAB_H

#include "tabs/details_tab.h"

#include <QStandardItemModel>

class AttributesModel;

// Show attributes of target as a list of attribute names and values
// Values are editable
class AttributesTab final : public DetailsTab {
Q_OBJECT

public:
    AttributesTab();

    void load(const AdObject &object) override;

private:
    AttributesModel *model;
};

class AttributesModel final : public QStandardItemModel {
Q_OBJECT

public:
    explicit AttributesModel(QObject *parent);

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    void load(const AdObject &object);
};

#endif /* ATTRIBUTES_TAB_H */
