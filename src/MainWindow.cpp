/* File: MainWindow.cpp
 * Holds a UI for the demo.
*/

#include "include/MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  m_gl = new NGLScene(this);
  ui->s_mainWindowGridLayout->addWidget(m_gl,2,0,2,1);
  connect(ui->m_wireFrame, SIGNAL(toggled(bool)), m_gl, SLOT(toggleWireframe(bool)));
  connect(ui->m_drawSelection, SIGNAL(currentIndexChanged(int)),m_gl, SLOT(setDrawMode(int)));
  connect(ui->m_reset, SIGNAL(clicked()), m_gl, SLOT(resetSim()));
  connect(ui->m_hairLength, SIGNAL(valueChanged(int)), m_gl, SLOT(setHairLength(int)));
  connect(ui->m_guideCount, SIGNAL(valueChanged(int)), m_gl, SLOT(setGuideCount(int)));
  connect(ui->m_followCount, SIGNAL(valueChanged(int)), m_gl, SLOT(setFollowCount(int)));
  connect(ui->m_hairLOD, SIGNAL(valueChanged(int)), m_gl, SLOT(setHairLOD(int)));
  connect(ui->m_toggleFocus, SIGNAL(clicked()), m_gl, SLOT(toggleFocus()));
}

MainWindow::~MainWindow()
{
  delete ui;
}
