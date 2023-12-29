#include "ImagesProcessing.hpp"

int main(){

    cv::Mat img = cv::imread("../Projects/Images/folha.bmp");
    cv::Mat rotated, translated;

    //Obtendo a matriz de rotação:
    cv::Mat m_rotacao = cv::getRotationMatrix2D(cv::Point2f(img.size().width/2,
                                                img.size().height/2), -90, 1);

    //Obtendo a matriz de translação:
    cv::Mat m_translacao = (cv::Mat_<float>(2,3) << 1, 0, 100, 0, 1, 100);

    //Aplicando a matriz na imagem original e gerando a imagem rotacionada:
    cv::warpAffine(img, rotated, m_rotacao, cv::Size(img.cols, img.cols));
    cv::warpAffine(img, translated, m_translacao, cv::Size(img.cols, img.cols));

    cv::resize(img, img, cv::Size(0,0), 0.5, 0.5, cv::INTER_CUBIC);
    
    cv::imshow("Original", img);
    cv::imshow("Rotated", rotated);
    cv::imshow("Translated", translated);

    cv::waitKey(0);
    
    return 0;

}

int channels_segmentation(){

    cv::String path = "../Projects/Images/clock.bmp";
    vector<cv::Mat> channels, channelsbgr;
    cv::Mat img = cv::imread(path), hue, saturation, value, vorta;
    cv::Vec3b valorPixel;
    int pixelhue, pixelblue;
    
    if (img.empty()){
        cerr << "Não possível carregar a imagem\n";
        return -1;
    }
    cv::resize(img, img, cv::Size(400, 300));
    cv::cvtColor(img, vorta, cv::COLOR_BGR2HSV);

    valorPixel = img.at<cv::Vec3b>(cv::Point(150,150));

    //segmentar canais hsv e bgr:
    cv::split(vorta, channels);
    cv::split(img, channelsbgr);

    hue = channels[0];
    saturation = channels[1];
    value = channels[2];
    
    hue = 0.55*hue;

    pixelhue = hue.at<uchar>(150,150);
    pixelblue = channelsbgr[0].at<uchar>(cv::Point(150,150));

    //combinar canais hsv novamente:
    cv::merge(channels, vorta);
    cv::cvtColor(vorta, vorta, cv::COLOR_HSV2BGR);


    cv::imshow("Original", img);
    cv::imshow("Hue", hue);
    cv::imshow("Saturation", saturation);
    cv::imshow("Value", value);
    cv::imshow("Modificada ", vorta);
    
    cout << valorPixel << endl;
    cout << pixelblue << endl;
    cout << pixelhue << endl;

    cv::waitKey(0);

    return 0;
}


int teste_class(){
    cv::String path = "../Projects/Images/eneas.jpg";
    cv::String build = "../Projects/Images/building.jpg";
    cv::Mat eneas = cv::imread(path), neg, resized, swapped, faces, warped, contours;

    if (eneas.empty()){
        cerr << "Erro ao carregar imagem\n";
        return -1;
    }

    ImagesProcessing teste(eneas);

    neg = teste.negative();
    resized = teste.resize();
    swapped = teste.swap();
    faces = teste.faceDetection();
    contours = teste.drawContours();

    teste.cut();

    //cv::bitwise_not(eneas, neg); função para negativar toda a imagem direto
    cv::imwrite("../Projects/Images/eneas_resized.jpg", resized );
    
    cv::imshow("Nosso nome é Enéas negativo", neg);
    cv::imshow("Redimensionada: ", resized);
    cv::imshow("Swapped", swapped);
    cv::imshow("Faces detectadas", faces);
    cv::imshow("Contours", contours);
    cv::imshow("Nosso nome é Enéas", eneas);

    cv::waitKey();

    return 0;


}