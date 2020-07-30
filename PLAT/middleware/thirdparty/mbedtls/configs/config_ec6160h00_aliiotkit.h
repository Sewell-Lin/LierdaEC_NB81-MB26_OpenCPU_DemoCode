/*
 *the mbedtls configuration file of ec616_0h00 aliiotkit project
 */

#ifndef MBEDTLS_CONFIG_ALIIOTKIT_H
#define MBEDTLS_CONFIG_ALIIOTKIT_H

#include "config_ec_dtls.h"
#define MBEDTLS_SSL_PROTO_DTLS
#define MBEDTLS_SSL_DTLS_HELLO_VERIFY
#define MBEDTLS_SSL_DTLS_CLIENT_PORT_REUSE
#define MBEDTLS_SSL_SESSION_TICKETS
#define MBEDTLS_X509_CHECK_KEY_USAGE
#define MBEDTLS_X509_CHECK_EXTENDED_KEY_USAGE
#define MBEDTLS_SSL_CACHE_C
#define MBEDTLS_SSL_COOKIE_C
#define MBEDTLS_SSL_TICKET_C
#define MBEDTLS_SSL_MAX_FRAGMENT_LENGTH
#define MBEDTLS_SSL_ALL_ALERT_MESSAGES
#define MBEDTLS_GENPRIME
#define MBEDTLS_ERROR_STRERROR_DUMMY
#define MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED
#define MBEDTLS_REMOVE_ARC4_CIPHERSUITES
#define MBEDTLS_CIPHER_PADDING_ZEROS
#define MBEDTLS_CIPHER_PADDING_PKCS7
#define MBEDTLS_CIPHER_MODE_CFB
#define MBEDTLS_GCM_C


#include "mbedtls/check_config.h"

#endif /* MBEDTLS_CONFIG_H */