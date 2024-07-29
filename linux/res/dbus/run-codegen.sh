gdbus-codegen \
    --interface-prefix=com.douki \
    --c-namespace Douki \
    --header \
    --output ../../include/dbus-credential.h \
    --pragma-once \
    v1/com.douki.Credential.xml

gdbus-codegen \
    --interface-prefix=com.douki \
    --c-namespace Douki \
    --body \
    --output ../../src/dbus/dbus-credential.c \
    v1/com.douki.Credential.xml