/**
 * Copyright (c) 2015 Runtime Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef H_BLE_HS_CONN_
#define H_BLE_HS_CONN_

#include "os/queue.h"
#include "ble_l2cap.h"
#include "ble_att_priv.h"
struct hci_le_conn_complete;
struct hci_create_conn;
struct ble_l2cap_chan;

struct ble_hs_conn {
    SLIST_ENTRY(ble_hs_conn) bhc_next;
    uint16_t bhc_handle;
    uint8_t bhc_addr[6];

    struct ble_l2cap_chan_list bhc_channels;
    uint16_t bhc_outstanding_pkts;

    struct ble_att_svr_conn bhc_att_svr;
};

struct ble_hs_conn *ble_hs_conn_alloc(void);
void ble_hs_conn_free(struct ble_hs_conn *conn);
void ble_hs_conn_insert(struct ble_hs_conn *conn);
void ble_hs_conn_remove(struct ble_hs_conn *conn);
struct ble_hs_conn *ble_hs_conn_find(uint16_t con_handle);
struct ble_hs_conn *ble_hs_conn_first(void);
struct ble_l2cap_chan *ble_hs_conn_chan_find(struct ble_hs_conn *conn,
                                             uint16_t cid);
void ble_hs_conn_rx_num_completed_pkts(uint16_t handle, uint16_t num_pkts);
int ble_hs_conn_can_tx(struct ble_hs_conn *conn);
int ble_hs_conn_init(void);

#endif
