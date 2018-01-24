/* Represents the UI of this demo. Created with the help of a tutorial by Jon Macey,
 * available at http://jonmacey.blogspot.co.uk/2011/03/using-qt-gui-components-and-ngl.html
 *
 * author: Chris Leu
 * version 1.0
 * date 26/1/18
 *
 * Revision History:
 *  Initial version 26/1/18
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "NGLScene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  NGLScene *m_gl;
};

#endif // MAINWINDOW_H
