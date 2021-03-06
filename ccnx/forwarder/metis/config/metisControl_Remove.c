/*
 * Copyright (c) 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Patent rights are not granted under this agreement. Patent rights are
 *       available under FRAND terms.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEROX or PARC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#include <config.h>

#include <stdbool.h>
#include <stdint.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

#include <LongBow/runtime.h>

#include <parc/security/parc_Security.h>

#include <parc/algol/parc_Memory.h>

#include <ccnx/forwarder/metis/config/metisControl_Remove.h>
#include <ccnx/forwarder/metis/config/metisControl_RemoveConnection.h>
#include <ccnx/forwarder/metis/config/metisControl_RemoveRoute.h>

static void _metisControlRemove_Init(MetisCommandParser *parser, MetisCommandOps *ops);
static MetisCommandReturn _metisControlRemove_Execute(MetisCommandParser *parser, MetisCommandOps *ops, PARCList *args);
static MetisCommandReturn _metisControlRemove_HelpExecute(MetisCommandParser *parser, MetisCommandOps *ops, PARCList *args);

static const char *_commandRemove = "remove";
static const char *_commandRemoveHelp = "help remove";

// ====================================================

MetisCommandOps *
metisControlRemove_Create(MetisControlState *state)
{
    return metisCommandOps_Create(state, _commandRemove, _metisControlRemove_Init, _metisControlRemove_Execute, metisCommandOps_Destroy);
}

MetisCommandOps *
metisControlRemove_HelpCreate(MetisControlState *state)
{
    return metisCommandOps_Create(state, _commandRemoveHelp, NULL, _metisControlRemove_HelpExecute, metisCommandOps_Destroy);
}

// ==============================================

static MetisCommandReturn
_metisControlRemove_HelpExecute(MetisCommandParser *parser, MetisCommandOps *ops, PARCList *args)
{
    MetisCommandOps *ops_remove_connection = metisControlRemoveConnection_Create(NULL);
    MetisCommandOps *ops_remove_route = metisControlRemoveRoute_Create(NULL);

    printf("Available commands:\n");
    printf("   %s\n", ops_remove_connection->command);
    printf("   %s\n", ops_remove_route->command);
    printf("\n");

    metisCommandOps_Destroy(&ops_remove_connection);
    metisCommandOps_Destroy(&ops_remove_route);
    return MetisCommandReturn_Success;
}

static void
_metisControlRemove_Init(MetisCommandParser *parser, MetisCommandOps *ops)
{
    MetisControlState *state = ops->closure;
    metisControlState_RegisterCommand(state, metisControlRemoveConnection_HelpCreate(state));
    metisControlState_RegisterCommand(state, metisControlRemoveRoute_HelpCreate(state));
    metisControlState_RegisterCommand(state, metisControlRemoveConnection_Create(state));
    metisControlState_RegisterCommand(state, metisControlRemoveRoute_Create(state));
}

static MetisCommandReturn
_metisControlRemove_Execute(MetisCommandParser *parser, MetisCommandOps *ops, PARCList *args)
{
    return _metisControlRemove_HelpExecute(parser, ops, args);
}
