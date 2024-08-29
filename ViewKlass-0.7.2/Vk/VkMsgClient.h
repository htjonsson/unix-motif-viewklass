/*****************************************************************
    ViewKlass - C++ framework library for Motif

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Copyright (C) 2001 John Lemcke
    jostle@users.sourceforge.net
*****************************************************************/

/**
 *
 * $Id: VkMsgClient.h,v 1.4 2003/04/08 11:31:42 jostle Exp $
 *
 * This file contains the class declaration for
 * VkMsgClient, which encapsulates the programmer's
 * interface to handling ToolTalk messages.
 *
 * Chris Toshok
 * Copyright (C) 1995
 * The Hungry Programmers, Inc.
 * All Rights Reserved
 *
 **/

#ifndef VKMSGCLIENT_H
#define VKMSGCLIENT_H

#include <Vk/VkConfig.h>
#include <Vk/VkMsgFacility.h>
#include <Vk/VkMsgMessage.h>

typedef Boolean (*VkMsgClientAction)(void*               /* clientData */,
                                     VkMsgFacilityReason /* reason */,
                                     VkMsgMessage        /* msg_in */,
                                     char*               /* op */,
                                     int                 /* argc */,
                                     VkMsgArg*           /* argv */
                                     );

                    
class VkMsgClient {
public:

  sendStringNotice(char *op ...);
  sendIntNotice(char *op ...);

  void composeBegin();
  void composeAdd(char *val, VkMsgMode mode = VK_MSG_IN);
  void composeAdd(int ival, VkMsgMode mode = VK_MSG_IN);
  void composeAdd(unsigned char *val, int len,
                  VkMsgMode mode VK_MSG_IN); 

  void sendNotice(char *op);
  VkMsgMessage sendRequest(char *op);
  VkMsgMessage sendSyncRequest(char *op);

  void sendStringFileNotice(char *op, char *file ...);
  void sendIntFileNotice(char *op, char *file ...);
  void sendFileNotice(char *op, char *file);
  void sendFileRequest(char *op, char *file);
  void sendSyncFileRequest(char *op, char *file);
};

#endif // VKMSGCLIENT_H
