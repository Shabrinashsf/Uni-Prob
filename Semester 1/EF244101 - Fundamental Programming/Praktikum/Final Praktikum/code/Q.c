#include <stdio.h>
#include <math.h>
// acc
int main()
{
    long long aX, aY, aZ;
    long long bX, bY, bZ;
    long long cX, cY, cZ;
    long long rA, rB, RD;
    scanf("%lld %lld %lld", &aX, &aY, &aZ);
    scanf("%lld %lld %lld", &bX, &bY, &bZ);
    scanf("%lld %lld %lld", &cX, &cY, &cZ);
    scanf("%lld %lld %lld", &rA, &rB, &RD);

    long long temp_ab = (bX - aX) * (bX - aX) + (bY - aY) * (bY - aY) + (bZ - aZ) * (bZ - aZ);
    long long temp_bc = (cX - bX) * (cX - bX) + (cY - bY) * (cY - bY) + (cZ - bZ) * (cZ - bZ);
    long long temp_ac = (cX - aX) * (cX - aX) + (cY - aY) * (cY - aY) + (cZ - aZ) * (cZ - aZ);

    double sqrt_jarak_ab = round(sqrt((double)temp_ab));
    double sqrt_jarak_bc = round(sqrt((double)temp_bc));
    double sqrt_jarak_ac = round(sqrt((double)temp_ac));

    long long r_ab_used = ceil(sqrt_jarak_ab / (double)RD);
    long long r_bc_used = ceil(sqrt_jarak_bc / (double)RD);
    long long r_ac_used = ceil(sqrt_jarak_ac / (double)RD);

    if (r_ac_used <= rA)
    {
        printf("NAH ID WIN, NO NEED TO STOP");
    }
    else if (r_ab_used + r_bc_used <= rA + rB)
    {
        printf("HHM BETTER TAKE ROCKET, STILL CAN WIN");
    }
    else
    {
        printf("GIVE UP ALREADY, MINING BETTER");
    }
}