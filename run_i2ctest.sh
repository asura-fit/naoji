#/bin/sh
# Nao上でテストを実施するスクリプトのサンプル.
# libjunitが必要.

/usr/lib/jvm/java-6-hotspot/bin/java -ea -Djava.library.path=.:native -cp /usr/share/java/junit.jar:naoji_test.jar:naoji.jar junit.textui.TestRunner jp.ac.fit.asura.naoji.i2c.I2CdevTest
