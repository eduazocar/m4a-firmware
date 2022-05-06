/*
 * Copyright (C) 2022 Mesh4all.org <mesh4all.org>
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at

 *   http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/**
 * @ingroup     brnim
 * @{
 *
 * @file
 * @brief       Border Router Neighborh Information Manager implementation
 *
 * @author      eduazocar <eduardoazocar7@gmail.com>
 * @author      RocioRojas <rociorojas391@gmail.com>
 *
 * @}
 */

#ifdef MODULE_BRNIM_CLIENT
#include "brnim.h"

static sock_udp_t _sock;

/**
 * @brief   GNRC netif
 */
static gnrc_netif_t *_netif;

/**
 * @brief   UDP local endpoint
 */
static sock_udp_ep_t _local;

static char _stack[THREAD_STACKSIZE_DEFAULT];

void brnim_thread(void){

}

uint8_t buf[7];
 
void main(void)
{
    sock_udp_ep_t local = SOCK_IPV6_EP_ANY;
    sock_udp_t sock;
 
    local.port = 0xabcd;
 
    if (sock_udp_create(&sock, &local, NULL, 0) < 0) {
        puts("Error creating UDP sock");
        return 1;
    }
 
 
    while (1) {
        sock_udp_ep_t remote = { .family = AF_INET6 };
        ssize_t res;
 
        remote.port = 12345;
        ipv6_addr_set_all_nodes_multicast((ipv6_addr_t *)&remote.addr.ipv6,
                                          IPV6_ADDR_MCAST_SCP_LINK_LOCAL);
        if (sock_udp_send(&sock, "Hello!", sizeof("Hello!"), &remote) < 0) {
            puts("Error sending message");
            sock_udp_close(&sock);
            return 1;
        }
        if ((res = sock_udp_recv(&sock, buf, sizeof(buf), 1 * US_PER_SEC,
                                NULL)) < 0) {
            if (res == -ETIMEDOUT) {
                puts("Timed out");
            }
            else {
                puts("Error receiving message");
            }
        }
        else {
            printf("Received message: \"");
            for (int i = 0; i < res; i++) {
                printf("%c", buf[i]);
            }
            printf("\"\n");
        }
        xtimer_sleep(1);
    }
 
    return 0;
}
#endif
/* Implementation of the module */
