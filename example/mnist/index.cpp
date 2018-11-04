#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#include "cactus.hpp"
#include <Eigen/Dense>

using namespace std;

int ReverseInt(int i)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return((int)ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

void read_Mnist_Label(string filename, vector<double>&labels)
{
    ifstream file(filename, ios::binary);
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        file.read((char*)&magic_number, sizeof(magic_number));
        file.read((char*)&number_of_images, sizeof(number_of_images));
        magic_number = ReverseInt(magic_number);
        number_of_images = ReverseInt(number_of_images);
        cout << "magic number = " << magic_number << endl;
        cout << "number of images = " << number_of_images << endl;


        for (int i = 0; i < number_of_images; i++)
        {
            unsigned char label = 0;
            file.read((char*)&label, sizeof(label));
            labels.push_back((double)label);
        }

    }
}

void read_Mnist_Images(string filename, vector<vector<double>>&images)
{
    ifstream file(filename, ios::binary);
    //unsigned char label;
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        
        file.read((char*)&magic_number, sizeof(magic_number));
        file.read((char*)&number_of_images, sizeof(number_of_images));
        file.read((char*)&n_rows, sizeof(n_rows));
        file.read((char*)&n_cols, sizeof(n_cols));
        magic_number = ReverseInt(magic_number);
        number_of_images = ReverseInt(number_of_images);
        n_rows = ReverseInt(n_rows);
        n_cols = ReverseInt(n_cols);

        cout << "magic number = " << magic_number << endl;
        cout << "number of images = " << number_of_images << endl;
        cout << "rows = " << n_rows << endl;
        cout << "cols = " << n_cols << endl;

        for (int i = 0; i < number_of_images; i++)
        {
            vector<double>tp;
            for (int r = 0; r < n_rows; r++)
            {
                for (int c = 0; c < n_cols; c++)
                {
                    unsigned char image = 0;
                    file.read((char*)&image, sizeof(image));
                    tp.push_back(image);
                }
            }
            images.push_back(tp);
        }
    }
}

using namespace cactus;
template<typename LT>
class Type{
public:
	Type(Tensor x,Tensor y):x_(x),y_(y) {}
	template<typename RT>
    int get() {
		std::cout << x_.get<LT>(0) << y_.get<RT>(0) << std::endl;
        return 1;
    }
	void run() {
		CASES(y_.dtype(), get<T>());
	}
private:
	Tensor x_;
	Tensor y_;
};
template<typename LT,typename RT>
void rexp(Tensor x,Tensor y) {
	std::cout << x.get<LT>(0) << y.get<RT>(0) << std::endl;
}
template<typename LT>
void lexp(Tensor x, Tensor y) {
	CASES(y.dtype(),(rexp<LT,T>(x,y)));
}
void exp(Tensor x,Tensor y){
	CASES(x.dtype(), (lexp<T>(x,y)));
}

int main()
{
	Tensor x(5),y(0.265);
	exp(x, y);

    /*vector<double>labels;
    read_Mnist_Label("train-labels.idx1-ubyte", labels);
    vector<vector<double>>images;
    read_Mnist_Images("train-images.idx3-ubyte", images);
    for (size_t i = 0; i < images.size(); i++)
    {
        for (size_t j = 0; j < images[0].size(); j++)
        {
            cout << images[i][j] << " ";
        }
    }*/
    /*Eigen::Array2d x(1.2,0.5);
    Eigen::Array2i y(1, 6);
    auto z=x + 4;
    std::cout << z << std::endl;*/
    return 0;
}