#include <QtTest/QtTest>
#include <valuespec.h>

class TestFunction : public QObject
{
    Q_OBJECT

    using VS = Devlib::ValueSpec;
private slots:
};

QTEST_MAIN(TestFunction)
#include "function.moc"
