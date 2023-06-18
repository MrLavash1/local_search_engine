/**
 * @file Doxyfile
 * @brief This is the configuration file for Doxygen.
 *
 * @details This file contains the configuration options for Doxygen.
 * It is used to generate documentation for the localSearchEngine project.
 *
 * @author
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

#include "header/ConvertJSON.h"
#include "header/InvertedIndex.h"
#include "header/SearchEngine.h"

int main(int argc, char *argv[])
{
    tm t;
    QApplication app(argc, argv);

    QWidget window;
    QVBoxLayout layout(&window);

    QTextEdit textEdit1;
    layout.addWidget(&textEdit1);

    QTextEdit textEdit2;
    layout.addWidget(&textEdit2);

    QPushButton button("Старт");
    layout.addWidget(&button);


    try
    {
        ConverterJSON data;
        InvertedIndex index;
        index.UpdateDocumentBase(data.GetTextDocuments());

        SearchServer search(index);
        data.PutAnswers(search.Search(data.GetRequests(), data.GetResponsesLimit()));


        QObject::connect(&button, &QPushButton::clicked, [&]() {
            QFile file1("../json/config.json"); // замените на имя вашего файла
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

    }
    catch (const ConfigFileEmpty_Exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (const ConfigFileMissing_Exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (const ConfigFileVersionEmpty_Exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (const ConfigFileVersionIncorrect_Exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (const RequestsFileEmpty_Exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (const RequestsFileMissing_Exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (const Text_ExceptionALotOf& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (const Word_Exception100Chars& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (const MoreThen1000Requests_Exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (const WordsRequests_Exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }









    window.show();

    return app.exec();


    return 0;
}