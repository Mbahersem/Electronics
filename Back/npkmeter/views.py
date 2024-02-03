from django.utils.decorators import method_decorator
# from corsheaders.decorators import cors_headers
from npkmeter.models import NPKpH
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status
import requests
import pickle
import datetime
import pandas as pd
import numpy as np

from npkmeter.serializers import NPKpHSerializer

# url = 'https://api.openweathermap.org/data/2.5/onecall?lat=3.8667&lon=11.5167&units=metric&exclude=alerts,hourly,minutely&appid=a03d6946088e1173a8d47e963ea36f23'
# r = requests.get(url)

def predict (data):
    liste_culture = []
    data = np.array(data).reshape(1, 6)
    with open("../model.pkl", "rb") as f :
        gnb = pickle.load(f)  
    classes = gnb.classes_[np.argsort(gnb.predict_proba(data), axis = 1)]
    for k in range((classes.shape[1]-1), -1, -1):
        liste_culture.append(classes[0][k])
    return liste_culture

# @method_decorator(cors_headers(), name='dispatch')
class BasicAPI(APIView):
    def get(self, request):
        q = NPKpH.objects.last()
        data = NPKpHSerializer(q)
        return Response(data.data)

    def post(self, request):
        data_weather = r.json()
        df_daily = pd.DataFrame(data_weather['daily'])
        headers_daily = df_daily.filter(items=['dt', 'temp','humidity', 'pop', 'rain', 'wind_speed'])
        headers_daily = pd.concat([df_daily.drop(['temp',
                                     'sunrise',
                                     'sunset',
                                     'weather',
                                     'moonrise',
                                     'moon_phase',
                                     'feels_like',
                                     'pressure',
                                     'wind_deg',
                                     'wind_gust',
                                     'clouds',
                                     'uvi',
                                     'moonset',
                                     'feels_like',
                                     'pressure',
                                     'dew_point'], axis=1),
                                    df_daily['temp'].apply(pd.Series)], axis=1)

        #These are the daily needed values to use. Very important, it give 7 days prediction
        needed_daily_values = headers_daily.filter(items=['dt', 'humidity','day', 'rain', 'wind_speed'])
        forecast_list = needed_daily_values.to_dict('records')

        time_values = [time["dt"] for time in forecast_list]
        
        dt = time_values[0]
        dt = datetime.datetime.fromtimestamp(dt)
        
        T = needed_daily_values.values[0][2]
        H = needed_daily_values.values[0][1]
        
        N = int(request.data.get('n'))
        P = int(request.data.get('p'))
        K = int(request.data.get('k'))
        ph = int(request.data.get('ph'))
        
        q = NPKpH(n = N, p = P, k = K, ph = ph, h = H, t = T)
        q.save()
        rep = NPKpHSerializer(q)
        return Response(rep.data, status=status.HTTP_200_OK)

# @method_decorator(cors_headers(), name='dispatch')
class PredictionAPI(APIView):
    def get(self, request):
        q = NPKpH.objects.last()
        n = q.n
        p = q.p
        k = q.k
        ph = q.ph
        t = q.t
        h = q.h
        crop = predict([n, p, k, t, h, ph])
        data = {
            "crops": crop
        }
        return Response(data, status=status.HTTP_200_OK)