#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <time.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <math.h>
#include <complex>
#include <iomanip>
#include <stdio.h>

using namespace sf;
using namespace std;

const int W = 900;
const int H = 600;
double zoom = 1.0;

//dichiaro le variabili per il calcolo dell'equazione
int max_iter = 128;//num. di iterazioni della funz. ricorisva
double min_re = -2;//valore minimo asse reale
double max_re = 1;//valore max asse reale
double min_im = -1;//valore min. asse immaginario
double max_im = 1;//valore max asse immaginario

//dichiaro le variabili statiche
static int x_fp = 0;
static int y_fp = 0;
static double xPoint;
static double yPoint;
static int numeroScelta;
static int numero_iterazioni_scelte;
//variabili per colorare i grafici dei frattali
static int n;
static int r;
static int g;
static int b;
//static vector <coppieCoordinate> listaPosizioniXY;

double w = (max_re - min_re) * 20.0/W;
double h = (max_im - min_im) * 20.0/H;


struct coppieCoordinate
{
    double x, y;
};

ostream& operator <<(ostream& stream, const coppieCoordinate& boh) {
    stream << boh.x << "," << boh.y;
    return stream;
}

//METODO CALCOLO ITERAZIONI

//*********** POSSIBILE SUGGERIMENTO PER L'UTENTE: DIRGLI QUANTO CONVERGE/DIVERGE IL PUNTO DA LUI SCELTO
//IN BASE AL CONFRONTO TRA NUMERO DI ITERAZIONI SCELTE E CONDIZIONE DI APPARTENENZA DEL WHILE(&& parteRealeZ * parteRealeZ + parteImmaginariaZ * parteImmaginariaZ < 4.0)************////
vector <coppieCoordinate> calcoloMandelbrot(double cr, double ci, int iterazioni_user) {
    int numeroRicorsioni = 0;
    double parteRealeZ = 0, parteImmaginariaZ = 0;
    vector <coppieCoordinate> listaCoordinate;

    while (numeroRicorsioni < iterazioni_user) {
        double temp = parteRealeZ * parteRealeZ - parteImmaginariaZ * parteImmaginariaZ + cr;
        parteImmaginariaZ = 2.0 * parteRealeZ * parteImmaginariaZ + ci;
        parteRealeZ = temp;
        numeroRicorsioni++;
        listaCoordinate.push_back({ parteRealeZ,parteImmaginariaZ });
    }
    //per stampare la lista delle coordinate
    for (int i = 0; i < listaCoordinate.size(); i++)
    {
        cout << listaCoordinate[i] << endl;
    }
    return listaCoordinate;
}

vector <coppieCoordinate> calcoloBurninhShip(double cr, double ci, int iterazioni_user) {
    int numeroRicorsioni = 0;
    double parteRealeZ = 0, parteImmaginariaZ = 0;
    vector <coppieCoordinate> listaCoordinate;
    while (numeroRicorsioni < iterazioni_user) {
        double temp = parteRealeZ * parteRealeZ - parteImmaginariaZ * parteImmaginariaZ + cr;
        parteImmaginariaZ = 2.0 * abs(parteRealeZ * parteImmaginariaZ) + ci;
        parteRealeZ = temp;
        numeroRicorsioni++;
        listaCoordinate.push_back({ parteRealeZ,parteImmaginariaZ });
    }
    //per stampare la lista delle coordinate
    for (int i = 0; i < listaCoordinate.size(); i++)
    {
        cout << listaCoordinate[i] << endl;
    }
    return listaCoordinate;

}
// SUGGERIMENTO PER DOPO : (&& cr * cr + ci * ci < 4.0)
vector <coppieCoordinate> calcoloJuliaSet1(double cr, double ci, int iterazioni_user) {
    double parteRealeC = -0.7269, parteImmaginariaC = 0.1889; // costante c di partenza del set
    int numeroRicorsioni = 0;
    vector <coppieCoordinate> listaCoordinate;
    listaCoordinate.push_back({ cr,ci });
    while (numeroRicorsioni < iterazioni_user - 1)
    {
        double tempX = cr * cr - ci * ci + parteRealeC;
        double tempY = 2.0 * cr * ci + parteImmaginariaC;
        cr = tempX;
        ci = tempY;
        numeroRicorsioni++;
        listaCoordinate.push_back({ cr,ci });

    }
    //per stampare la lista delle coordinate
    for (int i = 0; i < listaCoordinate.size(); i++)
    {
        cout << listaCoordinate[i] << endl;
    }
    return listaCoordinate;

}

// SUGGERIMENTO PER DOPO : (&& cr * cr + ci * ci < 4.0)
vector <coppieCoordinate> calcoloJuliaSet2(double cr, double ci, int iterazioni_user) {
    double parteRealeC = 0.285, parteImmaginariaC = 0.01; // costante c di partenza del set
    int numeroRicorsioni = 0;
    vector <coppieCoordinate> listaCoordinate;
    listaCoordinate.push_back({ cr,ci });
    while (numeroRicorsioni < iterazioni_user - 1)
    {
        double tempX = cr * cr - ci * ci + parteRealeC;
        double tempY = 2.0 * cr * ci + parteImmaginariaC;
        cr = tempX;
        ci = tempY;
        numeroRicorsioni++;
        listaCoordinate.push_back({ cr,ci });

    }
    //per stampare la lista delle coordinate
    for (int i = 0; i < listaCoordinate.size(); i++)
    {
        cout << listaCoordinate[i] << endl;
    }
    return listaCoordinate;

}

//METODO PER CALCOLO RICORSIONI FRATTALI;

//metodo per frattale di Mandelbrot
int ricorsioniMandelbrot(double cr, double ci, int max_iterations) {
    double parteRealeZ = 0, parteImmaginariaZ = 0;
    int numeroRicorsioni = 0;
    
    while (numeroRicorsioni < max_iter && parteRealeZ * parteRealeZ + parteImmaginariaZ * parteImmaginariaZ < 4.0)
    {
        double temp = parteRealeZ * parteRealeZ - parteImmaginariaZ * parteImmaginariaZ + cr;
        parteImmaginariaZ = 2.0 * parteRealeZ * parteImmaginariaZ + ci;
        parteRealeZ = temp;
        numeroRicorsioni++;
    }
    return numeroRicorsioni;
}



int ricorsioniJuliaSet1(double cr, double ci, int max_iterations) {
    double parteRealeC = -0.7269, parteImmaginariaC= 0.1889; // costante c di partenza del set
    int numeroRicorsioni = 0;
    while (numeroRicorsioni < max_iter && cr * cr + ci * ci < 4.0)
    {
        double tempX = cr * cr - ci * ci + parteRealeC;
        double tempY = 2.0 * cr * ci + parteImmaginariaC;
        cr = tempX;
        ci = tempY;
        numeroRicorsioni++;
       
    }
    return numeroRicorsioni;
}

int ricorsioniJuliaSet2(double cr, double ci, int max_iterations) {
    double parteRealeC = 0.285, parteImmaginariaC = 0.01; // costante c di partenza del set
    int numeroRicorsioni = 0;
    while (numeroRicorsioni < max_iter && cr * cr + ci * ci < 4.0)
    {
        double tempX = cr * cr - ci * ci + parteRealeC;
        double tempY = 2.0 * cr * ci + parteImmaginariaC;
        cr = tempX;
        ci = tempY;
        numeroRicorsioni++;

    }
    return numeroRicorsioni;
}

//metodo per frattale di Burning
int ricorsioniBurning_ship(double cr, double ci, int max_iterations) {
    double parteRealeZ = 0, parteImmaginariaZ = 0;
    int numeroRicorsioni = 0;

    while (numeroRicorsioni < max_iter && parteRealeZ * parteRealeZ + parteImmaginariaZ * parteImmaginariaZ < 4.0)
    {
        double temp = parteRealeZ * parteRealeZ - parteImmaginariaZ * parteImmaginariaZ + cr;
        parteImmaginariaZ = 2.0 * abs(parteRealeZ * parteImmaginariaZ) + ci;
        parteRealeZ = temp;
        numeroRicorsioni++;
    }
    return numeroRicorsioni;
}

//frattale di Chirikov
/*int chirikov(double cr, double ci, int max_iterations) {
    double parteRealeZ = 0, parteImmaginariaZ = 0;
    int numeroRicorsioni = 0;

    while (numeroRicorsioni < max_iter && parteRealeZ * parteRealeZ + parteImmaginariaZ * parteImmaginariaZ < 4.0) {
        double tempY =ci*sin(parteRealeZ);
        double tempX = cr * tempY;
        parteRealeZ = tempX;
        parteImmaginariaZ = tempY;
        numeroRicorsioni++;
    }
    return numeroRicorsioni;
} */

int henon(double cr, double ci, int max_iterations) {
    double parteRealeZ = 0, parteImmaginariaZ = 0;
    int numeroRicorsioni = 0;

    while (numeroRicorsioni < max_iter && parteRealeZ * parteRealeZ + parteImmaginariaZ * parteImmaginariaZ < 4.0)
    {
        double tempX = 1.0 - cr * parteRealeZ * parteRealeZ + parteImmaginariaZ;
        double tempY = ci * parteRealeZ;

        parteRealeZ = tempX;
        parteImmaginariaZ = tempY;
        numeroRicorsioni++;
    }
    return numeroRicorsioni;
}

int ikeda(double cr, double ci, int max_iterations) {
    double parteRealeZ = 0, parteImmaginariaZ = 0;
    int numeroRicorsioni = 0;

    while (numeroRicorsioni < max_iter && parteRealeZ * parteRealeZ + parteImmaginariaZ * parteImmaginariaZ < 4.0)
    {
        double t = 0.4 - 6.0 / (1.0 + parteRealeZ * parteRealeZ + parteImmaginariaZ * parteImmaginariaZ);
        double st = sin(t);
        double ct = cos(t);
        double tempX = 1.0 + cr * (parteRealeZ * ct - parteImmaginariaZ * st);
        double tempY = ci * (parteRealeZ * st + parteImmaginariaZ * ct);

        parteRealeZ = tempX;
        parteImmaginariaZ = tempY;
        numeroRicorsioni++;
    }
    return numeroRicorsioni;
}

//METODI CALCOLO COORDINATE

double nuovaCooridnataX(int x) {
    
    double new_x = min_re + (max_re - min_re) * x / W;
    return new_x;
}

double nuovaCooridnataY(int y) {
    double new_y =  -(min_im + (max_im - min_im) * y / H);
    return  new_y;
}
/*funzione che :
      A) calcola le coordinate in base alle iterazioni scelte;
      B) riempie il vettore con le coordinate
      C) restituisce in output il vettore
  */
static const vector<Color> colors{
                {0,0,0},
                {213,67,31},
                {251,255,121},
                {62,223,89},
                {43,30,218},
                {0,255,247}
};
Color linear_interpolation(const Color& v, const Color& u, double a)
{
    auto const b = 1 - a;
    return Color(b * v.r + a * u.r, b * v.g + a * u.g, b * v.b + a * u.b);
}

int main() {
    
    //simulazione di scelta funzione frattale da GUI
    //while (uscita == false) {
    cout << " digita 1 per mandelbrot, 2 per burning, 3 per julia set 1, 4 per julia set 2, 5 per henon, 6 per ikeda : "<< endl;
    cin >> numeroScelta;
    cout << " digita il numero di iterazioni che vuoi fare"<< endl;
    cin >> numero_iterazioni_scelte;
   

    RenderWindow window(sf::VideoMode(W,H), "Finestra Frattali");
    window.setFramerateLimit(30);
    glOrtho(0.0, window.getSize().x, window.getSize().y, 0.0, 1.0, -1.0);
    
    Image plotFrattale;
    plotFrattale.create(W, H);
    Texture texture;
    Sprite sprite;
    Font font;
    //font.loadFromFile("arial.ttf");
    Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            //per chiudere la window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            //per muovere l'immagine con le freccette della tastiera
            else if (event.type == Event::KeyPressed) {
                
                if (event.key.code == Keyboard::Left) { 
                    min_re -= w, max_re -= w;
                    xPoint -= w;
                    cout <<" coeff traslazione: " << w<< " la coordinata traslata e: " << xPoint << endl;
                    
                }
                if (event.key.code == Keyboard::Right) {
                    min_re += w, max_re += w; 
                    xPoint += w;
                    cout << " coeff traslazione: " << w << " la coordinata traslata e: " << xPoint << endl;

                }
                if (event.key.code == Keyboard::Up) {
                    min_im -= h, max_im -= h; 
                    yPoint -= h;
                    cout << " coeff traslazione: " << h << " la coordinata traslata e: " << yPoint << endl;
                }
                if (event.key.code == Keyboard::Down) {
                    min_im += h, max_im += h;
                    yPoint += h;
                    cout << " coeff traslazione: " << h << " la coordinata traslata e: " << yPoint << endl;
                    
                }

            }
            //per fare lo zoom
            else if (event.type == Event::MouseButtonPressed) {

                auto zoom_x = [&](double z)
                {
                    //mouse point will be new center point 
                    double cr = min_re + (max_re - min_re) * event.mouseButton.x / W;
                    double ci = min_im + (max_im - min_im) * event.mouseButton.y / H;
                    
                    //zoom
                    double tminr = cr - (max_re - min_re) / 2 / z;
                    max_re = cr + (max_re - min_re) / 2 / z;
                    min_re = tminr;
                    double tmini = ci - (max_im - min_im) / 2 / z;
                    max_im = ci + (max_im - min_im) / 2 / z;
                    min_im = tmini;
                };
                //Left Click to ZoomIn
                if (event.mouseButton.button == Mouse::Left) {
                    zoom_x(2);
                    zoom *= 2;
                }
                //Right Click to ZoomOut
                if (event.mouseButton.button == Mouse::Right) {
                    zoom_x(1.0 / 2);
                    zoom /= 2;
                }
            }
            //Set Iteration level by mouse wheel,the more iteration level the better image result
            else if (event.type == Event::MouseWheelScrolled) {
                if (event.MouseWheelScrolled) {
                    if (event.mouseWheelScroll.wheel == Mouse::VerticalWheel)
                    {
                        if (event.mouseWheelScroll.delta > 0) {
                            max_iter *= 2;
                        }
                        else max_iter /= 2;
                        if (max_iter < 1)max_iter = 1;
                    }
                }
            }
            else if (event.key.code == Keyboard::Enter) {
                const Vector2i mouse_pos = Mouse::getPosition(window);
                x_fp = mouse_pos.x;
                y_fp = mouse_pos.y;
                cout << "le coordinate del punto scelto sono: "<<"x :"<<x_fp<<" y: "<<y_fp<< endl;
                xPoint = nuovaCooridnataX(x_fp);
                cout << " la nuova coordinata x e :" << xPoint << endl;
                yPoint = nuovaCooridnataY(y_fp);
                cout << " la nuova coordinata y e :" << yPoint << endl;
                
                switch (numeroScelta)
                {
                case 1:
                    calcoloMandelbrot(xPoint, yPoint, numero_iterazioni_scelte);
                    break;
                case 2:
                    calcoloBurninhShip(xPoint, yPoint, numero_iterazioni_scelte);
                    break;
                case 3:
                    calcoloJuliaSet1(xPoint, yPoint, numero_iterazioni_scelte);
                    break;
                case 4:
                    calcoloJuliaSet2(xPoint, yPoint, numero_iterazioni_scelte);
                    break;
                }
                
            }
            
        }
    
        window.clear();
        switch (numeroScelta) {
        case 1:
#pragma omp parallel for
            //cicli for per frattale
            for (int y = 0; y < H; y++) {
                for (int x = 0; x < W; x++) {
                    //calcolo gli intervalli del set 
                    double cr = min_re + (max_re - min_re) * x / W;
                    double ci = min_im + (max_im - min_im) * y / H;
                    int n = ricorsioniMandelbrot(cr, ci, max_iter);
                    /*
                    int r = ((int)(n * sinf(n)) % 256);
                    int g = ((n * 3) % 256);
                    int b = (n % 256);
                    plotFrattale.setPixel(x, y, Color(r, g, b));
                    */
                    static const auto max_color = colors.size() - 1;
                    if (n == max_iter)
                        n = 0;
                    double mu = 1.0 * n / max_iter;
                    //scale mu to be in the range of colors
                    mu *= max_color;
                    auto i_mu = static_cast<size_t>(mu);
                    auto color1 = colors[i_mu];
                    auto color2 = colors[min(i_mu + 1, max_color)];
                    Color c = linear_interpolation(color1, color2, mu - i_mu);
                    plotFrattale.setPixel(x, y, Color(c));
                    
                }

            }

            break;

        case 2:
#pragma omp parallel for   
            //cicli for per frattale
            for (int y = 0; y < H; y++) {
                for (int x = 0; x < W; x++) {
                    //calcolo gli intervalli del set 
                    double cr = min_re + (max_re - min_re) * x / W;
                    double ci = min_im + (max_im - min_im) * y / H;
                    int n = ricorsioniBurning_ship(cr, ci, max_iter);
                    /* 
                    int r = ((int)(n * sinf(n)) % 256);
                    int g = ((n * 3) % 256);
                    int b = (n % 256);
                    */
                   
                    static const auto max_color = colors.size() - 1;
                    if (n == max_iter)
                        n = 0;
                    double mu = 1.0 * n / max_iter;
                    //scale mu to be in the range of colors
                    mu *= max_color;
                    auto i_mu = static_cast<size_t>(mu);
                    auto color1 = colors[i_mu];
                    auto color2 = colors[min(i_mu + 1, max_color)];
                    Color c = linear_interpolation(color1, color2, mu - i_mu);
                    plotFrattale.setPixel(x, y, Color(c));
                    //plotFrattale.setPixel(x, y, Color(r, g, b));

                }
            }
            break;
        case 3:
#pragma omp parallel for   
            //cicli for per frattale
            for (int y = 0; y < H; y++) {
                for (int x = 0; x < W; x++) {
                    //calcolo gli intervalli del set 
                    double cr = min_re + (max_re - min_re) * x / W;
                    double ci = min_im + (max_im - min_im) * y / H;
                    int n = ricorsioniJuliaSet1(cr, ci, max_iter);
                    
                    /*
                   int r = ((int)(n * sinf(n)) % 256);
                   int g = ((n * 3) % 256);
                   int b = (n % 256);
                   */

                    static const auto max_color = colors.size() - 1;
                    if (n == max_iter)
                        n = 0;
                    double mu = 1.0 * n / max_iter;
                    //scale mu to be in the range of colors
                    mu *= max_color;
                    auto i_mu = static_cast<size_t>(mu);
                    auto color1 = colors[i_mu];
                    auto color2 = colors[min(i_mu + 1, max_color)];
                    Color c = linear_interpolation(color1, color2, mu - i_mu);
                    plotFrattale.setPixel(x, y, Color(c));
                }
            }
            break;
        case 4:
#pragma omp parallel for   
            //cicli for per frattale
            for (int y = 0; y < H; y++) {
                for (int x = 0; x < W; x++) {
                    //calcolo gli intervalli del set 
                    double cr = min_re + (max_re - min_re) * x / W;
                    double ci = min_im + (max_im - min_im) * y / H;
                    int n = ricorsioniJuliaSet2(cr, ci, max_iter);
                    /*
                    int r = ((int)(n * sinf(n)) % 256);
                    int g = ((n * 3) % 256);
                    int b = (n % 256);
                    */

                    static const auto max_color = colors.size() - 1;
                    if (n == max_iter)
                        n = 0;
                    double mu = 1.0 * n / max_iter;
                    //scale mu to be in the range of colors
                    mu *= max_color;
                    auto i_mu = static_cast<size_t>(mu);
                    auto color1 = colors[i_mu];
                    auto color2 = colors[min(i_mu + 1, max_color)];
                    Color c = linear_interpolation(color1, color2, mu - i_mu);
                    plotFrattale.setPixel(x, y, Color(c));

                }
            }

            break;
        case 5:
#pragma omp parallel for   
            //cicli for per frattale julia
            for (int y = 0; y < H; y++) {
                for (int x = 0; x < W; x++) {
                    //calcolo gli intervalli del set 
                    double cr = min_re + (max_re - min_re) * x / W;
                    double ci = min_im + (max_im - min_im) * y / H;
                    int n = henon(cr, ci, max_iter);
                    /*
                   int r = ((int)(n * sinf(n)) % 256);
                   int g = ((n * 3) % 256);
                   int b = (n % 256);
                   */

                    static const auto max_color = colors.size() - 1;
                    if (n == max_iter)
                        n = 0;
                    double mu = 1.0 * n / max_iter;
                    //scale mu to be in the range of colors
                    mu *= max_color;
                    auto i_mu = static_cast<size_t>(mu);
                    auto color1 = colors[i_mu];
                    auto color2 = colors[min(i_mu + 1, max_color)];
                    Color c = linear_interpolation(color1, color2, mu - i_mu);
                    plotFrattale.setPixel(x, y, Color(c));
                }
            }

            break;
        case 6:
#pragma omp parallel for   
            //cicli for per frattale julia
            for (int y = 0; y < H; y++) {
                for (int x = 0; x < W; x++) {
                    //calcolo gli intervalli del set 
                    double cr = min_re + (max_re - min_re) * x / W;
                    double ci = min_im + (max_im - min_im) * y / H;
                    int n = ikeda(cr, ci, max_iter);
                    int r = ((int)(n * sinf(n)) % 256);
                    int g = ((n * 3) % 256);
                    int b = (n % 256);
                    plotFrattale.setPixel(x, y, Color(r, g, b));
                }
            }
        }
                
                texture.loadFromImage(plotFrattale);
                sprite.setTexture(texture);
                window.draw(sprite);

                char str[100];
                sprintf_s(str, "max iter:%d\nzoom:x%2.2lf", max_iter, zoom);
                text.setString(str);
                window.draw(text);
                window.display();
                /*cout << " per uscire premi x";
                cin  >> risposta;
                cout << "risposta :" << risposta<< " boolean: "<< uscita; */
                

                /*
                if (risposta != "x")
                {
                    window.clear();
                    
                }
                else {
                    uscita == true;
                    //window.clear();
                    window.close();
                    break;
                      
                }
                */        
            }
    return 0;
}
