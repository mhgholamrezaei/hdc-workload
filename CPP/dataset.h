#ifndef DATASET_H
#define DATASET_H

#define DATASET "EMG_Hand"
typedef struct {
    int test_size;
    int train_size; 
    int sample_size;
    int** train_val; 
    int* train_label; 
    int** test_val; 
    int* test_label;
} dataset_t, *pdataset_t;

int load_dataset(pdataset_t &pdataset) {

    /* Read the parameters */
    {
        std::string filename = "./dataset/";
        filename += DATASET;
        filename += "/parameters";

        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file " << filename << std::endl;
            return 1;
        }

        std::string line;
        std::getline(file, line);
        pdataset->test_size = std::stoi(line);
        std::getline(file, line);
        pdataset->train_size = std::stoi(line);
        std::getline(file, line);
        pdataset->sample_size = std::stoi(line);
        file.close();     
    }

    /* Read the train vlaues*/
    {
        std::string filename = "./dataset/";
        filename += DATASET;
        filename += "/train.val";

        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file " << filename << std::endl;
            return 1;
        }

        std::string line;
        pdataset->train_val = (int**) malloc (sizeof(int*) * pdataset->train_size); /* Memory Allocation*/
        int sample_idx = 0;
        int num;    
        while (std::getline(file, line)) {
            std::istringstream iss(line); // Use istringstream to parse the string
            int point_idx = 0;
            pdataset->train_val[sample_idx] = (int*) malloc (sizeof(int) * pdataset->sample_size); /* Memory Allocation*/
            while (iss >> num) {
                pdataset->train_val[sample_idx][point_idx] = num;
                point_idx ++;
            }
            sample_idx ++; 
        }
    }

    /* Read the train labels*/
    {
        std::string filename = "./dataset/";
        filename += DATASET;
        filename += "/train.label";

        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file " << filename << std::endl;
            return 1;
        }

        std::string line;
        pdataset->train_label = (int*) malloc (sizeof(int) * pdataset->train_size); /* Memory Allocation*/
        int sample_idx = 0;
        int num;    
        while (std::getline(file, line)) {
            std::istringstream iss(line); // Use istringstream to parse the string
            iss >> num;
            pdataset->train_label[sample_idx] = num;
            sample_idx ++; 
        }
    }


    /* Read the test vlaues*/
    {
        std::string filename = "./dataset/";
        filename += DATASET;
        filename += "/test.val";

        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file " << filename << std::endl;
            return 1;
        }

        std::string line;
        pdataset->test_val = (int**) malloc (sizeof(int*) * pdataset->test_size); /* Memory Allocation*/
        int sample_idx = 0;
        int num;    
        while (std::getline(file, line)) {
            std::istringstream iss(line); // Use istringstream to parse the string
            int point_idx = 0;
            pdataset->test_val[sample_idx] = (int*) malloc (sizeof(int) * pdataset->sample_size); /* Memory Allocation*/
            while (iss >> num) {
                pdataset->test_val[sample_idx][point_idx] = num;
                point_idx ++;
            }
            sample_idx ++; 
        }
    }

    /* Read the test labels*/
    {
        std::string filename = "./dataset/";
        filename += DATASET;
        filename += "/test.label";

        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file" << std::endl;
            return 1;
        }

        std::string line;
        pdataset->test_label = (int*) malloc (sizeof(int) * pdataset->test_size); /* Memory Allocation*/
        int sample_idx = 0;
        int num;    
        while (std::getline(file, line)) {
            std::istringstream iss(line); // Use istringstream to parse the string
            iss >> num;
            pdataset->test_label[sample_idx] = num;
            
            sample_idx ++; 
        }
    }

    return 0;
}

int get_checksum(pdataset_t &pdataset) { 
    int N = (1L << 20);
    int acc = 0;
    
    for (int sample_idx = 0; sample_idx < pdataset->train_size; sample_idx++)
    {
        for (int point_idx = 0; point_idx < pdataset->sample_size; point_idx++)
        {
            acc = (pdataset->train_val[sample_idx][point_idx] + acc) % N;
        }
    }

    for (int sample_idx = 0; sample_idx < pdataset->test_size; sample_idx++)
    {
        for (int point_idx = 0; point_idx < pdataset->sample_size; point_idx++)
        {
            acc = (pdataset->test_val[sample_idx][point_idx] + acc) % N;
        }
    }

    return acc; 
}

#endif