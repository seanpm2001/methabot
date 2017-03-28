/*-
 * lmopt.h
 * This file is part of libmetha
 *
 * Copyright (C) 2008, Emil Romanus <emil.romanus@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 * 
 * http://bithack.se/projects/methabot/
 */

#ifndef _LMOPT__H_
#define _LMOPT__H_

typedef enum {
    /* LMOPT_MODE                 = 0, */
    LMOPT_NUM_THREADS             = 1,
    LMOPT_INITIAL_CRAWLER         = 2,
    LMOPT_ENABLE_BUILTIN_PARSERS,
    LMOPT_IO_VERBOSE,
    LMOPT_USERAGENT,
    LMOPT_PRIMARY_SCRIPT_DIR,
    LMOPT_SECONDARY_SCRIPT_DIR,
    LMOPT_PRIMARY_CONF_DIR,
    LMOPT_SECONDARY_CONF_DIR,
    LMOPT_PROXY,
    LMOPT_ENABLE_COOKIES,
    LMOPT_MODULE_DIR,
    LMOPT_STATUS_FUNCTION,
    LMOPT_TARGET_FUNCTION,
    LMOPT_ERROR_FUNCTION,
    LMOPT_WARNING_FUNCTION,
    LMOPT_EV_FUNCTION,
} LMOPT;

typedef enum {
    LMSTAT_NUM_DISCARDED_URLS = 0,
} LMSTAT;

#endif
