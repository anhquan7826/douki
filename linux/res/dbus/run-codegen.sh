gdbus-codegen \
    --interface-prefix=com.anhquan.DoukiDbus1 \
    --c-namespace DoukiDbus \
    --header \
    --output ../../include/iface-credential.h \
    --pragma-once \
    v1/com.anhquan.DoukiDbus.Credential.xml

gdbus-codegen \
    --interface-prefix=com.anhquan.UnisyncDbus1 \
    --c-namespace UnisyncDbus \
    --body \
    --output ../../src/dbus/iface-credential.c \
    v1/com.anhquan.DoukiDbus.Credential.xml