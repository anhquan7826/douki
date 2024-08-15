gdbus-codegen \
    --interface-prefix=com.anhquan.douki \
    --c-namespace Douki \
    --header \
    --output ../../include/dbus-authentication.h \
    --pragma-once \
    v1/authentication.xml

gdbus-codegen \
    --interface-prefix=com.anhquan.douki \
    --c-namespace Douki \
    --body \
    --output ../../src/core/dbus/authentication.c \
    v1/authentication.xml