from npkmeter.models import NPKpH
from rest_framework import serializers

class NPKpHSerializer(serializers.ModelSerializer):
    class Meta:
        model = NPKpH
        fields = '__all__'