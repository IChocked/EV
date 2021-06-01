//
//  wheelRatio.cpp
//
//
//  Created by Isha G on 4/29/21.
//

const double inputVals[] = {0.00164959,  0.003299386, 0.004908535, 0.006526768, 0.008135816, 0.009735552, 0.011325855,
                            0.012906608, 0.014477703, 0.016039035, 0.017590506, 0.019132025, 0.020663506, 0.022184867,
                            0.023694297, 0.025194691, 0.026684654, 0.028164116, 0.029633009, 0.031091272, 0.032538847,
                            0.033975681, 0.035401727, 0.036816941, 0.038221282, 0.039614716, 0.040997211, 0.04236874,
                            0.043729279, 0.04507881,  0.046417316, 0.047744785, 0.049061209, 0.050366584, 0.051660906,
                            0.052944177, 0.054216403, 0.055477591, 0.05672775};

const double outputVals[] = {1.006982184, 1.013966383, 1.020954613, 1.027948894, 1.034951256, 1.041963737, 1.048988385,
                             1.056027263, 1.063082453, 1.070156054, 1.077250185, 1.084366993, 1.091508648, 1.098677354,
                             1.105875343, 1.113104884, 1.120368285, 1.127667895, 1.135006107, 1.142385361, 1.14980815,
                             1.157277021, 1.164794578, 1.17236349,  1.17998649,  1.187666384, 1.195406051, 1.203208451,
                             1.211076628, 1.219013716, 1.227022945, 1.235107644, 1.243271253, 1.25151732,  1.259849518,
                             1.268271644, 1.276787631, 1.285401556, 1.294117647};

const int arrLength = sizeof(inputVals) / sizeof(inputVals[0]);

double getRatio(double sensorVal)
{
    int low = 0;
    int high = inputVals.length - 1;

    if (sensorVal < inputVals[low])
    {
        return outputVals[low];
    }

    if (sensorVal > inputVals[high])
    {
        return outputVals[high];
    }

    while (high >= low)
    {
        int mid = (low + high) / 2;

        if (abs(inputVals[mid] - sensorVal) < 0.00085)
        {
            return outputVals[mid];
        }
        else if (inputVals[mid] < sensorVal)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
}
