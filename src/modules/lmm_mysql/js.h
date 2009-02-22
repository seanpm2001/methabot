/*-
 * js.h
 * This file is part of lmm_mysql
 *
 * Copyright (C) 2009, Emil Romanus <emil.romanus@gmail.com>
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
 * http://bithack.se/projects/methabot/modules/lmm_mysql/
 */


#ifndef _LMM_MYSQL_JS__H_
#define _LMM_MYSQL_JS__H_

#include <jsapi.h>

extern struct JSClass MySQLClass;
extern struct JSClass MySQLResultClass;
extern JSFunctionSpec lmm_MySQLClass_functions[];
extern JSFunctionSpec lmm_MySQLResultClass_functions[];

JSBool lmm_MySQLClass_construct(JSContext *cx, JSObject *this, uintN argc, jsval *argv, jsval *ret);

#endif
