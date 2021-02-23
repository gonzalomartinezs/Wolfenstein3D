#include <QMessageBox>
#include <string>

#ifndef EDITOR_MESSAGEBOX_H
#define EDITOR_MESSAGEBOX_H

/*Clase POPUP, tiene una serie de slots que al ser disparados generan un popUp
 * con el mensaje seleccionado.
 */
class MessageBox : public QMessageBox {
    Q_OBJECT
public:
    explicit MessageBox(QWidget* parent = nullptr);
public slots:
    void showYamlError();
    void showInstructions();
};

#endif //EDITOR_MESSAGEBOX_H