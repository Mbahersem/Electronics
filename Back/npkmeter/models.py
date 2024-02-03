from django.db import models

# Create your models here.

class NPKpH(models.Model):
    n = models.IntegerField(default=0)
    p = models.IntegerField(default=0)
    k = models.IntegerField(default=0)
    ph = models.IntegerField(default=0)
    t = models.IntegerField(default=0)
    h = models.IntegerField(default=0)
    
    def __str__(self) -> str:
        return str(self.n) + " " + str(self.p) + " " + str(self.k) + " " + str(self.ph)