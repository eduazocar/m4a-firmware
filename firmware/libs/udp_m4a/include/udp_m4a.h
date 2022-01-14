/*
 * Copyright (c) 2021 Mesh4all <mesh4all.org>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @{
 * @file        udp_m4a.h
 * @brief       udp libs
 * @author      xkevin190 <kevinvelasco190@gmail.com.com>
 *
 */

#ifndef UDP_M4A_H
#define UDP_M4A_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief this is a struct  used for init udp server
 */
typedef struct
{
   char* port;                                   /*!< port where will listen udp server */
   void (*callback) (uint8_t*, size_t len);      /*!< this is a callback this function will
                                                      be executed when arrive new values
                                                 */
} udpf_payload;

/**
 * @brief  udp server function this function is used for init udp server
 *
 * @param argv [in] this param will content  the callback and port where will listen el server
 * @return  0 Satisfactory result
 *         -1 Failed result
 */
int udp_server(udpf_payload* argv);

/**
 * @brief this function is used for send the sensors values
 *
 * @param port  [in]            port to which the message will be sent
 * @param address [int]         address to which the message will be sent
 * @param message [int]         in this parameter the sensor data will be sent
 * @param payload_len [int]     size of the message
 * @return int
 */
int udp_send(int* port, char* address, uint8_t* message, size_t* payload_len);

#ifdef __cplusplus
}
#endif
#endif /* UDP_M4A_H */
