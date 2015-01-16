/*
 * Copyright (c) 2014 NLNet Labs
 * Copyright (c) 2014 OpenDNSSEC AB (svb)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef DAEMON_CLIENTPIPE_H
#define DAEMON_CLIENTPIPE_H

#ifdef __cplusplus
extern "C" {
#endif

/* 1 on succes 0 on fail*/
int client_printf(int sockfd, const char * format, ...);
int client_printf_err(int sockfd, const char * format, ...);

/**
 * Client part of prompt handling
 * 
 * Block on stdin and send to daemon
 * 
 * \param sockfd, pipe to daemon.
 * \return 1 success, 0 error
 */
int client_handleprompt(int sockfd);

/**
 * Daemon part of prompt handling
 * 
 * Send question to client and block on getting an answer
 * 
 * \param sockfd, pipe to client
 * \param question, string to prompt the client with
 * \param[out] answer, client response. MUST be at least ODS_SE_MAXLINE long.
 * \return 0 on failure, 1 on success and answer will be set
 * 
 *  TODO: don't let it fail on partial read. */
int client_prompt_user(int sockfd, const char *question, char *answer);

enum msg_type {
	CLIENT_OPC_STDOUT = 0, 
	CLIENT_OPC_STDERR, 
	CLIENT_OPC_STDIN, 
	CLIENT_OPC_PROMPT, 
	CLIENT_OPC_EXIT
};

/* 1 on succes, 0 on fail */
int client_exit(int sockfd, char exitcode);
int client_stdin(int sockfd, const char *cmd, int count);
int client_stdout(int sockfd, const char *cmd, int count);
int client_stderr(int sockfd, const char *cmd, int count);
int client_prompt(int sockfd, const char *cmd, int count);

#ifdef __cplusplus
}
#endif

#endif /* DAEMON_CLIENTPIPE_H */
