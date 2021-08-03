/*
 * ADMC - AD Management Center
 *
 * Copyright (C) 2020-2021 BaseALT Ltd.
 * Copyright (C) 2020-2021 Dmitry Degtyarev
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

#include "edits/unlock_edit.h"
#include "adldap.h"
#include "utils.h"
#include <QCheckBox>
#include <QFormLayout>

const QString label_text = QCoreApplication::translate("UnlockEdit", "Unlock account");

UnlockEdit::UnlockEdit(QList<AttributeEdit *> *edits_out, const UnlockEditStyle style_arg, QObject *parent)
: AttributeEdit(edits_out, parent) {
    style = style_arg;

    // NOTE: if check is on left, then put text in the
    // checkbox
    const QString check_text = [&]() {
        switch (style) {
            case UnlockEditStyle_CheckOnLeft: return label_text;
            case UnlockEditStyle_CheckOnRight: return QString();
        }
        return QString();
    }();

    check = new QCheckBox(check_text);

    connect(
        check, &QCheckBox::stateChanged,
        [this]() {
            emit edited();
        });
}

void UnlockEdit::load_internal(AdInterface &ad, const AdObject &object) {
    check->setChecked(false);
}

void UnlockEdit::set_read_only(const bool read_only) {
    check->setDisabled(read_only);
}

void UnlockEdit::add_to_layout(QFormLayout *layout) {
    switch (style) {
        case UnlockEditStyle_CheckOnLeft: {
            layout->addRow(check);

            break;
        }
        case UnlockEditStyle_CheckOnRight: {
            layout->addRow(QString("%1:").arg(label_text), check);

            break;
        }
    }
}

bool UnlockEdit::apply(AdInterface &ad, const QString &dn) const {

    if (check->isChecked()) {
        const bool result = ad.user_unlock(dn);
        check->setChecked(false);

        return result;
    } else {
        return true;
    }
}
