/**
 * @file Doxyfile
 * @brief This is the configuration file for Doxygen.
 *
 * @details This file contains the configuration options for Doxygen.
 * It is used to generate documentation for the localSearchEngine project.
 *
 * @author Mark
 *
 */

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>

#include <iostream>
#include <string>


#include "header/ConvertJSON.h"
#include "header/InvertedIndex.h"
#include "header/SearchEngine.h"
#include <QLineEdit>
#include <QFileDialog>


int main(int argc, char *argv[])
{
    tm t;
    QApplication app(argc, argv);
    QString fileName;

    QWidget window;
    window.resize(600, 800);
    QVBoxLayout layout(&window);

    QLineEdit lineEdit;
    layout.addWidget(&lineEdit);
    QPushButton browsButton("Browse...");
    layout.addWidget(&browsButton);


    QLabel label("Информация о Движке");
    layout.insertWidget(2, &label);


    QTextEdit textEdit1;
    layout.addWidget(&textEdit1);

    QTextEdit textEdit2;
    layout.addWidget(&textEdit2);
    QLabel label2("Результат движка");
    layout.insertWidget(4, &label2);


    QPushButton startButton("Старт");
    layout.addWidget(&startButton);
    QPushButton closeButton("Закрыть");
    layout.addWidget(&closeButton);

    QObject::connect(&browsButton, &QPushButton::clicked, [&]() {
        textEdit1.clear();
        textEdit2.clear();
        fileName = QFileDialog::getOpenFileName(&window, "Открыть файл конфигурации", "", "Файлы JSON (*.json)");
        if (!fileName.isEmpty()) {
            lineEdit.setText(fileName);
        }


    });


    QObject::connect(&startButton, &QPushButton::clicked, [&]() {

        try
        {
            ConverterJSON data;
            InvertedIndex index;

            index.UpdateDocumentBase(data.GetTextDocuments(fileName.toStdString()));

            SearchServer search(index);
            data.PutAnswers(search.Search(data.GetRequests(), data.GetResponsesLimit()));




        }
        catch (const ConfigFileEmpty_Exception& ex)
        {
            textEdit1.setPlainText(ex.what());

        }
        catch (const ConfigFileMissing_Exception& ex)
        {
            textEdit1.setPlainText(ex.what());

        }
        catch (const ConfigFileVersionEmpty_Exception& ex)
        {
            textEdit1.setPlainText(ex.what());

        }
        catch (const ConfigFileVersionIncorrect_Exception& ex)
        {
            textEdit1.setPlainText(ex.what());

        }
        catch (const RequestsFileEmpty_Exception& ex)
        {
            textEdit1.setPlainText(ex.what());

        }
        catch (const RequestsFileMissing_Exception& ex)
        {
            textEdit1.setPlainText(ex.what());

        }
        catch (const Text_ExceptionALotOf& ex)
        {
            textEdit1.setPlainText(ex.what());

        }
        catch (const Word_Exception100Chars& ex)
        {
            textEdit1.setPlainText(ex.what());

        }
        catch (const MoreThen1000Requests_Exception& ex)
        {
            textEdit1.setPlainText(ex.what());

        }
        catch (const WordsRequests_Exception& ex)
        {
            textEdit1.setPlainText(ex.what());

        }


        QObject::connect(&startButton, &QPushButton::clicked, [&]() {
            QFile file1(fileName); // замените на имя вашего файла
            if (file1.open(QIODevice::ReadOnly)) {
                QByteArray data = file1.readAll();
                QJsonDocument doc = QJsonDocument::fromJson(data);
                QJsonObject json = doc.object();

                // используйте объект json

                textEdit1.setPlainText(doc.toJson(QJsonDocument::Indented));
            }


            QFile file2("../json/answers.json");
            if (file2.open(QIODevice::ReadOnly)) {
                QByteArray data = file2.readAll();
                QJsonDocument doc = QJsonDocument::fromJson(data);
                QJsonObject json = doc.object();

                QString text;
                QJsonObject answers = json["answers"].toObject();
                for (auto it = answers.begin(); it != answers.end(); ++it) {
                    text += it.key() + ":\n";
                    QJsonObject answer = it.value().toObject();
                    QJsonArray relevance = answer["relevance"].toArray();
                    for (const auto &element: relevance) {
                        text += "    " + element.toString() + "\n";
                    }
                    text += "    \"result\": \"" + answer["result"].toString() + "\"\n\n";
                }

                textEdit2.setPlainText(text);
            }
        });
    });


    QObject::connect(&closeButton, &QPushButton::clicked, [&]() {
        window.close();
    });


    window.show();

    return app.exec();

}
