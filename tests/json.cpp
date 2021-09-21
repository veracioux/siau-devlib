#include <QtTest/QtTest>

#include "json.h"
#include <QByteArray>
#include <QDir>
#include <QFile>
#include <QJsonObject>
#include <iostream>
#include <limits>
#include <unistd.h>

using namespace Devlib;

namespace Devlib
{
extern QJsonObject jsonObjectFromFile(const QString&);
}

class TestJson : public QObject
{
    Q_OBJECT

    ValueSpec specFromFile(const QString& path)
    {
        auto obj = jsonObjectFromFile(path);
        return jsonParseValueSpec(obj);
    }

private slots:

    void testValueSpecEmpty()
    {
        auto spec = specFromFile("valuespec/empty.json");
        QVERIFY(spec.isVoid());
        QVERIFY(spec.getValueRange().isEmpty());
        QVERIFY(spec.getUnit().isEmpty());
    }

    void testValueSpecBool()
    {
        auto spec = specFromFile("valuespec/bool.json");
        QVERIFY(spec.isBool());
        QVERIFY(spec.getValueRange().isEmpty());
    }

    void testValueSpecFloat()
    {
        auto spec = specFromFile("valuespec/float.json");
        QVERIFY(spec.isFloat());
        QCOMPARE(spec.getMinFloat(), 0.3f);
        QCOMPARE(spec.getMaxFloat(), 2.3f);
    }

    void testValueSpecCustomEnum()
    {
        auto spec = specFromFile("valuespec/enum.json");
        QVERIFY(spec.isCustomEnum());
        QCOMPARE(spec.getValueType(), "Status");
        QCOMPARE(spec.getValueRange(), (QStringList{"On", "Off"}));
    }

    void testValueSpecFloat_OnlyType()
    {
        auto spec = specFromFile("valuespec/float_only_type.json");
        QVERIFY(spec.isFloat());
        QVERIFY(qIsNaN(spec.getMinFloat()));
        QVERIFY(qIsNaN(spec.getMaxFloat()));
    }

    void testValueSpecInt()
    {
        auto spec = specFromFile("valuespec/int.json");
        QVERIFY(spec.isInt());
        QCOMPARE(spec.getMinInt(), -4);
        QCOMPARE(spec.getMaxInt(), 10);
        QCOMPARE(spec.getUnit(), "%");
    }

    void testValueSpecInt_OnlyType()
    {
        auto spec = specFromFile("valuespec/int_only_type.json");
        QVERIFY(spec.isInt());
        QCOMPARE(spec.getMinInt(), std::numeric_limits<int>::min());
        QCOMPARE(spec.getMaxInt(), std::numeric_limits<int>::max());
        QVERIFY(spec.getUnit().isEmpty());
    }

    void testValueSpecWrongAttributeTypes()
    {
        QJsonObject obj = jsonObjectFromFile("valuespec/wrong_attributes.json");
        foreach (const QString& attr, obj.keys()) {
            QVERIFY_EXCEPTION_THROWN(
              jsonParseValueSpec(obj.value(attr).toObject()),
              std::runtime_error);
        }
    }

    void testValueSpecIntegrated()
    {
        auto spec = specFromFile("function/single.json");
        QVERIFY(spec.isFloat());
        QCOMPARE(spec.getMinFloat(), 0);
        QCOMPARE(spec.getMaxFloat(), 100);
        QCOMPARE(spec.getUnit(), "%");
    }

    void testData()
    {
        auto obj = jsonObjectFromFile("data/data.json");
        Data* data = jsonParseData(obj);
        QCOMPARE(data->getName(), "AnInt");
        QCOMPARE(data->getFriendlyName(), "An integer");
        ValueSpec spec = data->getValueSpec();
        QVERIFY(spec.isInt());
        QCOMPARE(spec.getValueRange(), (QStringList{ "-5", "40" }));
        QCOMPARE(spec.getUnit(), "%");
        delete data;
    }

    void testSingleFunction()
    {
        auto obj = jsonObjectFromFile("function/single.json");
        SingleFunction* function = jsonParseFunction(obj);
        QCOMPARE(function->getName(), "setBrightness");
        QCOMPARE(function->getFriendlyName(), "Set Brightness");
        ValueSpec spec = function->getValueSpec();
        QVERIFY(spec.isFloat());
        QCOMPARE(spec.getValueRange(), (QStringList{ "0", "100" }));
        QCOMPARE(spec.getUnit(), "%");
        delete function;
    }

    void testMultiFunction()
    {
        auto obj = jsonObjectFromFile("function/multi.json");
        QJsonArray multiFunction = obj["function"].toArray();
        MultiFunction *mfun = jsonParseFunction(multiFunction);
        auto sfunList = mfun->getSingleFunctions();
        QCOMPARE(sfunList.size(), 2);

        SingleFunction *sfun1 = sfunList[0], *sfun2 = sfunList[1];

        QCOMPARE(sfun1->getName(), "turnOn");
        QVERIFY(sfun1->getValueSpec().isVoid());

        QCOMPARE(sfun2->getName(), "turnOff");
        QVERIFY(sfun2->getValueSpec().isVoid());
    }

    void testDevice()
    {
        Device device = jsonParseDevice("device/device.json");
        QCOMPARE(device.getName(), "TestDevice");
        QCOMPARE(device.getVendorId(), "ETF");
        QCOMPARE(device.getModel(), "Model-X");
        QCOMPARE(device["deviceType"], "Generic"); // TODO

        QList<Function*> functions = device.getFunctions();
        QVERIFY(functions.length() == 2);
        QVERIFY(functions[0]->isSingleFunction());

        SingleFunction* sfun = dynamic_cast<SingleFunction*>(functions[0]);
        QVERIFY(sfun != nullptr);

        QCOMPARE(sfun->getName(), "setBrightness");
        QCOMPARE(sfun->getFriendlyName(), "Set Brightness");
        auto valueSpec = sfun->getValueSpec();
        QVERIFY(valueSpec.isFloat());
        QCOMPARE(valueSpec.getValueRange(), (QStringList{ "0", "100" }));
        QCOMPARE(valueSpec.getUnit(), "%");

        MultiFunction* mfun = dynamic_cast<MultiFunction*>(functions[1]);
        SingleFunction *sfun1 = mfun->getSingleFunctions()[0],
                *sfun2 = mfun->getSingleFunctions()[1];
        QVERIFY(mfun != nullptr);
        QCOMPARE(sfun1->getName(), "turnOn");
        QVERIFY(sfun1->getValueSpec().isVoid());
        QCOMPARE(sfun2->getName(), "turnOff");
        QVERIFY(sfun2->getValueSpec().isVoid());

        QList<Data*> data = device.getData();
        QVERIFY(data.length() == 1);
        QCOMPARE(data[0]->getName(), "getBrightness");
        QCOMPARE(data[0]->getFriendlyName(), "Brightness");
        valueSpec = data[0]->getValueSpec();
        QVERIFY(valueSpec.isInt());
        QCOMPARE(valueSpec.getValueRange(), (QStringList{ "-5", "40" }));
        QCOMPARE(valueSpec.getUnit(), "%");
    }
};

QTEST_MAIN(TestJson)
#include "json.moc"
