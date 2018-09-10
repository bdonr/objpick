

#include "CgQtGLRenderWidget.h"
#include "CgQtGui.h"
#include "CgQtMainApplication.h"
#include "../CgBase/CgEnums.h"
#include "../CgEvents/CgMouseEvent.h"
#include "../CgEvents/CgKeyEvent.h"
#include "../CgEvents/CgWindowResizeEvent.h"
#include "../CgEvents/CgLoadObjFileEvent.h"
#include "../CgEvents/CgTrackballEvent.h"
#include "../Nclass/myevent.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QGroupBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QMenuBar>
#include <QActionGroup>
#include <QFileDialog>
#include <iostream>



CgQtGui::CgQtGui(CgQtMainApplication *mw)
    : m_mainWindow(mw)
{
    m_glRenderWidget = new CgQtGLRenderWidget;
    traeger = new TraegerKlasse();

    connect(m_glRenderWidget, SIGNAL(mouseEvent(QMouseEvent*)), this, SLOT(mouseEvent(QMouseEvent*)));
    connect(m_glRenderWidget, SIGNAL(viewportChanged(int,int)), this, SLOT(viewportChanged(int,int)));
    connect(m_glRenderWidget, SIGNAL(trackballChanged()), this, SLOT(slotTrackballChanged()));


    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;


    QWidget *opt = new QWidget;
    createOptionPanelExample1(opt);

    QWidget *otheropt = new QWidget;
    createOptionPanelExample2(otheropt);

    QTabWidget* m_tabs = new QTabWidget();
    m_tabs->addTab(opt,"&My Tab1");
    m_tabs->addTab(otheropt,"&My Tab2");
    container->addWidget(m_tabs);

    m_tabs->setMaximumWidth(400);
 //   m_tabs->setMinimumWidth(300);
  //  m_tabs->setMinimumHeight(600);
    container->addWidget(m_glRenderWidget);

    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);

    setLayout(mainLayout);
    setWindowTitle(tr("Übung Computergrafik 1 -  SoSe 2018"));


    /* create Menu Bar */
    m_menuBar = new QMenuBar;
    QMenu *file_menu = new QMenu("&File" );
    file_menu->addAction("&Open Mesh Model", this, SLOT(slotLoadMeshFile()));
    // todo: Add Quit-Action
    m_menuBar->addMenu( file_menu );
    QMenu *settings_menu = new QMenu("&Setting" );
    QMenu *polygon_mode_menu = new QMenu("&Polygon Mode" );

    QAction* m_custom_rot=settings_menu->addAction("&Custom Rotations", m_glRenderWidget, SLOT(slotCustomRotation()));
    m_custom_rot->setCheckable(true);
    m_custom_rot->setChecked(false);

    QAction* m_lighting=settings_menu->addAction("&Lighting on", m_glRenderWidget, SLOT(slotLighting()));
    m_lighting->setCheckable(true);
    m_lighting->setChecked(false);


    QActionGroup* polygonmode_group = new QActionGroup(this);
    polygonmode_group->setExclusive(true);

    QAction* points=polygon_mode_menu->addAction("&Points", m_glRenderWidget, SLOT(slotPolygonPoints()));
    points->setCheckable(true);
    points->setChecked(false);


    QAction* wireframe=polygon_mode_menu->addAction("&Wireframe", m_glRenderWidget, SLOT(slotPolygonWireframe()));
    wireframe->setCheckable(true);
    wireframe->setChecked(true);

    QAction* filled=polygon_mode_menu->addAction("&Filled", m_glRenderWidget, SLOT(slotPolygonFilled()));
    filled->setCheckable(true);
    filled->setChecked(false);



    polygonmode_group->addAction(points);
    polygonmode_group->addAction(wireframe);
    polygonmode_group->addAction(filled);



    // todo: Add Quit-Action
    m_menuBar->addMenu( file_menu );
    m_menuBar->addMenu( settings_menu );
    m_menuBar->addMenu( polygon_mode_menu );


    m_mainWindow->setMenuBar(m_menuBar);



}

QSlider *CgQtGui::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}







void CgQtGui::createOptionPanelExample1(QWidget* parent)
{
    QVBoxLayout *tab1_control = new QVBoxLayout();


    /*Example for using a label */

    QLabel *options_label = new QLabel("Options");
    tab1_control->addWidget(options_label);
    options_label->setAlignment(Qt::AlignCenter);


    /*Example for using a spinbox */

    mySpinBox1 = new QSpinBox();
    tab1_control->addWidget(mySpinBox1);
    mySpinBox1->setMinimum(1);
    mySpinBox1->setMaximum(50);
    mySpinBox1->setValue(3);
   // mySpinBox1->setSuffix("   suffix");
   // mySpinBox1->setPrefix("Prefix:  ");
    connect(mySpinBox1, SIGNAL(valueChanged(int) ), this, SLOT(slotMySpinBox1Changed()) );
    tab1_control->addWidget(mySpinBox1);


    /*Example for using a checkbox */

    myCheckBox1 = new QCheckBox("enable Option 1");
    myCheckBox1->setCheckable(true);
    myCheckBox1->setChecked(false);
    connect(myCheckBox1, SIGNAL( clicked() ), this, SLOT(slotMyCheckBox1Changed()) );
    tab1_control->addWidget(myCheckBox1);


    /*Example for using a button */

    QPushButton* myButton1 = new QPushButton("&drueck mich");
    tab1_control->addWidget(myButton1);

    connect(myButton1, SIGNAL( clicked() ), this, SLOT(slotMyButton1Pressed()) );



    parent->setLayout(tab1_control);

}

void CgQtGui::createOptionPanelExample2(QWidget* parent)
{


    QVBoxLayout *tab2_control = new QVBoxLayout();
    QHBoxLayout *subBox = new QHBoxLayout();


     QPushButton* myButton10 = new QPushButton("&Zentral");
     QPushButton* myButton11 = new QPushButton("&Paralel");
     subBox->addWidget(myButton10);
     subBox->addWidget(myButton11);

     connect(myButton10, SIGNAL( clicked() ), this, SLOT(slotChangeProjektionZentral()) );
     connect(myButton11, SIGNAL( clicked() ), this, SLOT(slotChangeProjektionParalel()) );
//-----------------------------
     QLabel *label = new QLabel("Frustum R/10");
     tab2_control->addWidget(label);
     label->setAlignment(Qt::AlignCenter);

     mySpinBox1 = new QSpinBox();
     tab2_control->addWidget(mySpinBox1);
     mySpinBox1->setMinimum(1);
     mySpinBox1->setMaximum(30);
     mySpinBox1->setValue(10);
     connect(mySpinBox1, SIGNAL(valueChanged(int) ), this, SLOT(slotChangeFrustumR(int)));
//_____________
     QLabel *label2 = new QLabel("Frustum L/10");
     tab2_control->addWidget(label2);
     label2->setAlignment(Qt::AlignCenter);

     QSpinBox* mySpinBox2 = new QSpinBox();
     tab2_control->addWidget(mySpinBox2);
     mySpinBox2->setMinimum(1);
     mySpinBox2->setMaximum(30);
     mySpinBox2->setValue(10);
     connect(mySpinBox2, SIGNAL(valueChanged(int) ), this, SLOT(slotChangeFrustumL(int)) );
//____________
     QLabel *label3 = new QLabel("Frustum T/10");
     tab2_control->addWidget(label3);
     label3->setAlignment(Qt::AlignCenter);

     QSpinBox* mySpinBox3 = new QSpinBox();
     tab2_control->addWidget(mySpinBox3);
     mySpinBox3->setMinimum(1);
     mySpinBox3->setMaximum(30);
     mySpinBox3->setValue(10);
     connect(mySpinBox3, SIGNAL(valueChanged(int) ), this, SLOT(slotChangeFrustumT(int)) );
//____________
     QLabel *label4 = new QLabel("Frustum B/10");
     tab2_control->addWidget(label4);
     label4->setAlignment(Qt::AlignCenter);

     QSpinBox* mySpinBox4 = new QSpinBox();
     tab2_control->addWidget(mySpinBox4);
     mySpinBox4->setMinimum(1);
     mySpinBox4->setMaximum(30);
     mySpinBox4->setValue(10);
     connect(mySpinBox4, SIGNAL(valueChanged(int) ), this, SLOT(slotChangeFrustumB(int)) );
//____________
     QLabel *label5 = new QLabel("Frustum F/10");
     tab2_control->addWidget(label5);
     label5->setAlignment(Qt::AlignCenter);

     QSpinBox* mySpinBox5 = new QSpinBox();
     tab2_control->addWidget(mySpinBox5);
     mySpinBox5->setMinimum(1);
     mySpinBox5->setMaximum(30);
     mySpinBox5->setValue(10);
     connect(mySpinBox5, SIGNAL(valueChanged(int) ), this, SLOT(slotChangeFrustumF(int)) );
//____________
     QLabel *label6 = new QLabel("Frustum N/10");
     tab2_control->addWidget(label6);
     label6->setAlignment(Qt::AlignCenter);

     QSpinBox* mySpinBox6 = new QSpinBox();
     tab2_control->addWidget(mySpinBox6);
     mySpinBox6->setMinimum(1);
     mySpinBox6->setMaximum(30);
     mySpinBox6->setValue(10);
     connect(mySpinBox6, SIGNAL(valueChanged(int) ), this, SLOT(slotChangeFrustumN(int)) );
//____________

     tab2_control->addLayout(subBox);
     parent->setLayout(tab2_control);

}



void CgQtGui::slotButtonGroupSelectionChanged()
{

}

void CgQtGui::slotMySpinBox1Changed()
{

}

void CgQtGui::slotMyCheckBox1Changed()
{

}


void CgQtGui::slotLoadMeshFile()
{



   QString file=  QFileDialog::getOpenFileName(this, tr("Open Obj-File"),"",tr("Model Files (*.obj)"));


    CgBaseEvent* e = new CgLoadObjFileEvent(Cg::LoadObjFileEvent, file.toStdString());

    notifyObserver(e);
}

void CgQtGui::slotChangeProjektionParalel()
{
    traeger->setProjektion(1);
    CgBaseEvent* e = new MyEvent(Cg::CgchangeProjektion, traeger);
    notifyObserver(e);
}

void CgQtGui::slotChangeProjektionZentral()
{
    traeger->setProjektion(2);
    CgBaseEvent* e = new MyEvent(Cg::CgchangeProjektion, traeger);
    notifyObserver(e);
}

void CgQtGui::slotChangeFrustumR(int i)
{
    traeger->setFrustumTyp(0);
    traeger->setFrustumValue(i);
    CgBaseEvent* e = new MyEvent(Cg::CgchangeFrustum, traeger);
    notifyObserver(e);
}

void CgQtGui::slotChangeFrustumL(int i)
{
    traeger->setFrustumTyp(1);
    traeger->setFrustumValue(i);
    CgBaseEvent* e = new MyEvent(Cg::CgchangeFrustum, traeger);
    notifyObserver(e);
}

void CgQtGui::slotChangeFrustumT(int i)
{
    traeger->setFrustumTyp(2);
    traeger->setFrustumValue(i);
    CgBaseEvent* e = new MyEvent(Cg::CgchangeFrustum, traeger);
    notifyObserver(e);
}

void CgQtGui::slotChangeFrustumB(int i)
{
    traeger->setFrustumTyp(3);
    traeger->setFrustumValue(i);
    CgBaseEvent* e = new MyEvent(Cg::CgchangeFrustum, traeger);
    notifyObserver(e);
}

void CgQtGui::slotChangeFrustumN(int i)
{
    traeger->setFrustumTyp(4);
    traeger->setFrustumValue(i);
    CgBaseEvent* e = new MyEvent(Cg::CgchangeFrustum, traeger);
    notifyObserver(e);
}

void CgQtGui::slotChangeFrustumF(int i)
{
    traeger->setFrustumTyp(5);
    traeger->setFrustumValue(i);
    CgBaseEvent* e = new MyEvent(Cg::CgchangeFrustum, traeger);
    notifyObserver(e);
}

void CgQtGui::slotTrackballChanged()
{
    CgBaseEvent* e = new CgTrackballEvent(Cg::CgTrackballEvent, m_glRenderWidget->getTrackballRotation());
    notifyObserver(e);
}

void CgQtGui::slotMyButton1Pressed()
{
   std::cout << "button 1 pressed " << std::endl;
}


void CgQtGui::mouseEvent(QMouseEvent* event)
{

   // std::cout << QApplication::keyboardModifiers() << std::endl;

  //  if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)==true)
    //    std::cout << Cg::ControlModifier << endl;


   if(event->type()==QEvent::MouseButtonPress)
   {


        CgBaseEvent* e = new CgMouseEvent(Cg::CgMouseButtonPress,
                                          glm::vec2(event->localPos().x() ,event->localPos().y()),
                                          (Cg::MouseButtons)event->button());

        notifyObserver(e);
   }

   if(event->type()==QEvent::MouseMove)
   {
       CgBaseEvent* e= new CgMouseEvent(Cg::CgMouseMove,
                                        glm::vec2(event->localPos().x() ,event->localPos().y()),
                                        (Cg::MouseButtons)event->button());
       notifyObserver(e);
   }



}

void CgQtGui::keyPressEvent(QKeyEvent *event)
{
   CgBaseEvent* e= new CgKeyEvent(Cg::CgKeyPressEvent,(Cg::Key)event->key(),(Cg::KeyboardModifiers)event->nativeModifiers(),event->text().toStdString());
   notifyObserver(e);
}


void CgQtGui::viewportChanged(int w, int h)
{
     CgBaseEvent* e = new CgWindowResizeEvent(Cg::WindowResizeEvent,w,h);
     notifyObserver(e);
}




CgBaseRenderer* CgQtGui::getRenderer()
{
    return m_glRenderWidget;
}





