#include "chip.h"
#include "mainwindow.h"
#include "view.h"

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageRegionIteratorWithIndex.h"

#include <QHBoxLayout>
#include <QSplitter>
#include <QImage>

#include <iterator>

MainWindow::MainWindow(QWidget *parent)
: QWidget(parent)
{
    populateScene();
    
    /*h1Splitter = new QSplitter;
    h2Splitter = new QSplitter;
    
    QSplitter *vSplitter = new QSplitter;
    vSplitter->setOrientation(Qt::Vertical);
    vSplitter->addWidget(h1Splitter);
    vSplitter->addWidget(h2Splitter);*/
    
    View *view = new View("Projet Master 2");
    view->view()->setScene(scene);
    //h1Splitter->addWidget(view);
    
    /*view = new View("Top right view");
    view->view()->setScene(scene);
    h1Splitter->addWidget(view);
    
    view = new View("Bottom left view");
    view->view()->setScene(scene);
    h2Splitter->addWidget(view);
    
    view = new View("Bottom right view");
    view->view()->setScene(scene);
    h2Splitter->addWidget(view);*/
    
    QHBoxLayout *layout = new QHBoxLayout;
    //layout->addWidget(vSplitter);
    layout->addWidget(view);
    setLayout(layout);
    
    setWindowTitle(tr("Projet Synthese Master 2"));
}

void MainWindow::populateScene()
{
    scene = new QGraphicsScene(this);
    
    typedef itk::RGBPixel< unsigned char > RGBPixelType;
    typedef itk::Image< RGBPixelType, 2 > ImageType;
    typedef itk::ImageFileReader<ImageType> ReaderType;

    ReaderType::Pointer reader = ReaderType::New();
    //reader->SetFileName(":/qt4logo.png");
    std::string fileName;
    std::cout << "Image : " << std::endl;
    std::cin >> fileName;
    reader->SetFileName(fileName);
    reader->Update();

    ImageType::Pointer myITKImage = reader->GetOutput();

    ImageType::RegionType region = myITKImage->GetLargestPossibleRegion();

    ImageType::SizeType size = region.GetSize();

    int h=size[0] , w=size[1];

    QImage myQtImage(h,w,QImage::Format_RGB32);

    itk::ImageRegionIteratorWithIndex<ImageType> it(myITKImage,size);

    std::cout << "myITKImage->GetLargestPossibleRegion().GetSize() : " << myITKImage->GetLargestPossibleRegion().GetSize() << std::endl;

    it.GoToBegin();

    for (unsigned int j=0;j<w;j++)
    {
      for (unsigned int i=0;i<h;i++)
      {
        RGBPixelType v = it.Get();
        unsigned int qvalue = 0;
        unsigned int r = v.GetRed();
        unsigned int g = v.GetGreen();
        unsigned int b = v.GetBlue();
        /*std::cout<< "Rouge : "<< r << std::endl;
        std::cout<< "Vert : "<< g << std::endl;
        std::cout<< "Bleu : "<< b << std::endl;*/
        qvalue = (r << 16) + (g << 8) + b;
        //std::cout << qvalue << std::endl;
        myQtImage.setPixel(i,j,qvalue);
        //std::cout << it.Get() << std::endl;
        //std::cout << myQtImage.pixel(i,j) << std::endl;
        ++it;
      }
    }
    
    // Populate scene
    int xx = 0;
    int nitems = 0;
    for (int i = -10000; i < 10000; i += 100) {
        ++xx;
        int yy = 0;
        for (int j = -10000; j < 10000; j += 100) {
            ++yy;
            qreal x = (i + 10000) / 20000.0;
            qreal y = (j + 10000) / 20000.0;
            
            QColor color(myQtImage.pixel(int(myQtImage.width() * x), int(myQtImage.height() * y)));
            QGraphicsItem *item = new Chip(color, xx, yy);
            item->setPos(QPointF(i, j));
            scene->addItem(item);
            
            ++nitems;
        }
    }
    std::cout << "Nombre de pixels : " << nitems << std::endl;
}

