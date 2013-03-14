# -------------------------------------------------
# Project created by QtCreator 2013-03-13T09:36:26
# -------------------------------------------------
QT -= core \
    gui
TARGET = polarSSL
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
INCLUDEPATH += ../include
SOURCES += ../app/test.c \
    ../library/xtea.c \
    ../library/x509write.c \
    ../library/x509parse.c \
    ../library/version.c \
    ../library/timing.c \
    ../library/ssl_tls.c \
    ../library/ssl_srv.c \
    ../library/ssl_cli.c \
    ../library/ssl_cache.c \
    ../library/sha4.c \
    ../library/sha2.c \
    ../library/sha1.c \
    ../library/rsa.c \
    ../library/pkcs11.c \
    ../library/pem.c \
    ../library/pbkdf2.c \
    ../library/padlock.c \
    ../library/net.c \
    ../library/mem.c \
    ../library/md_wrap.c \
    ../library/md5.c \
    ../library/md4.c \
    ../library/md2.c \
    ../library/md.c \
    ../library/havege.c \
    ../library/gcm.c \
    ../library/error.c \
    ../library/entropy_poll.c \
    ../library/entropy.c \
    ../library/dhm.c \
    ../library/des.c \
    ../library/debug.c \
    ../library/ctr_drbg.c \
    ../library/cipher_wrap.c \
    ../library/cipher.c \
    ../library/certs.c \
    ../library/camellia.c \
    ../library/blowfish.c \
    ../library/bignum.c \
    ../library/base64.c \
    ../library/asn1write.c \
    ../library/asn1parse.c \
    ../library/arc4.c \
    ../library/aes.c \
    ../app/simple_rsa.c
OTHER_FILES += 
