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

#include "console_drag_model.h"

#include "ad_interface.h"
#include "status.h"
#include "object_model.h"

#include <QMimeData>
#include <QString>
#include <QUrl>

// TODO: dragging queries and query folders
// TODO: move object_can_drop() and object_drop() here, shouldnt be in AD() 

QMimeData *ConsoleDragModel::mimeData(const QModelIndexList &indexes) const {
    QMimeData *data = QStandardItemModel::mimeData(indexes);

    const QList<QUrl> dns =
    [=]() {
        QList<QUrl> out;
        for (const QModelIndex index : indexes) {
            if (index.column() == 0) {
                const QString dn = index.data(Role_DN).toString();
                out.append(dn);
            }
        }

        return out;
    }();

    data->setUrls(dns);

    return data;
}

bool ConsoleDragModel::canDropMimeData(const QMimeData *data, Qt::DropAction, int row, int, const QModelIndex &parent) const {
    if (!data->hasUrls()) {
        return false;
    }

    const bool dropping_between_rows = (row != -1);
    if (dropping_between_rows) {
        return false;
    }

    const QList<QUrl> dns = data->urls();

    if (dns.size() == 1) {
        const QString dn = dns[0].toString();
        const QString parent_dn = parent.siblingAtColumn(0).data(Role_DN).toString();

        return AD()->object_can_drop(dn, parent_dn);
    } else {
        // NOTE: no checks are done for whether multiple items can be dropped, for performance reasons
        return true;
    }
}

bool ConsoleDragModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int, const QModelIndex &parent) {
    // TODO: implement dropping next to parent (which happens if row or column aren't equal to -1). In that case would need to insert within other rows instead of just appending.
    const bool dropping_between_rows = (row != -1);
    if (dropping_between_rows) {
        return false;
    }

    if (!data->hasUrls()) {
        return true;
    }

    const QList<QUrl> dns = data->urls();
    const QString target_dn = parent.siblingAtColumn(0).data(Role_DN).toString();

    STATUS()->start_error_log();

    for (const QUrl dn : dns) {
        AD()->object_drop(dn.toString(), target_dn);
    }

    STATUS()->end_error_log(nullptr);

    return true;
}