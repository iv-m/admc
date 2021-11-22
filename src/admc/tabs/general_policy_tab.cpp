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

#include "tabs/general_policy_tab.h"
#include "tabs/ui_general_policy_tab.h"

#include "adldap.h"
#include "attribute_edits/datetime_edit.h"
#include "utils.h"

#include <QDebug>

// NOTE: missing "comment" and "owner" field, BUT not sure
// about their inclusion. They straddle the boundary between
// admc/gpui. On windows they are displayed/editable in both
// GPM(admc equivalent) and GPME(gpui equivalent). Comment
// is stored somewhere on sysvol. Owner, not sure, might be
// in security descriptor?

GeneralPolicyTab::GeneralPolicyTab() {
    ui = new Ui::GeneralPolicyTab();
    ui->setupUi(this);

    auto created_edit = new DateTimeEdit(ui->created_edit, ATTRIBUTE_WHEN_CREATED, &edits, this);
    auto modified_edit = new DateTimeEdit(ui->modified_edit, ATTRIBUTE_WHEN_CHANGED, &edits, this);

    created_edit->set_read_only(true);
    modified_edit->set_read_only(true);

    edits_connect_to_tab(edits, this);
}

GeneralPolicyTab::~GeneralPolicyTab() {
    delete ui;
}

void GeneralPolicyTab::load(AdInterface &ad, const AdObject &object) {
    // Load version strings
    const int ad_version = object.get_int(ATTRIBUTE_VERSION_NUMBER);

    int sysvol_version = 0;
    const bool get_sysvol_version_success = ad.gpo_get_sysvol_version(object, &sysvol_version);

    auto get_machine_version = [](const int version_number) {
        const int out = version_number & 0x0000FFFF;

        return out;
    };

    auto get_user_version = [](const int version_number) {
        int out = version_number & 0xFFFF0000;

        out = out >> 16;

        return out;
    };

    const int ad_user = get_user_version(ad_version);
    const int sysvol_user = get_user_version(sysvol_version);
    const int ad_machine = get_machine_version(ad_version);
    const int sysvol_machine = get_machine_version(sysvol_version);

    // If we fail to load version from sysvol, show
    // "unknown" instead of number
    const QString unknown_string = tr("unknown");

    const QString sysvol_user_string = [&]() {
        if (get_sysvol_version_success) {
            return QString::number(sysvol_user);
        } else {
            return unknown_string;
        }
    }();

    const QString sysvol_machine_string = [&]() {
        if (get_sysvol_version_success) {
            return QString::number(sysvol_machine);
        } else {
            return unknown_string;
        }
    }();

    const QString user_version_string = QString("%1 (AD), %2 (sysvol)").arg(ad_user).arg(sysvol_user_string);
    const QString machine_version_string = QString("%1 (AD), %2 (sysvol)").arg(ad_machine).arg(sysvol_machine_string);

    ui->computer_version_label->setText(machine_version_string);
    ui->user_version_label->setText(user_version_string);

    const QString id = object.get_string(ATTRIBUTE_CN);
    ui->unique_id_label->setText(id);

    PropertiesTab::load(ad, object);
}