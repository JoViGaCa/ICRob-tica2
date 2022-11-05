


const double g,z, Gi, Gx, Gd;

int main(){
    double matrix_A[3][3] = {{0,1,0},{g/z, 0, -g/z},{0,0,0}};

    //achar o u

    double vet_u[3];
    vet_u[0]= -Gi * sum(c*vet_x[0] - sensor_ref[0]) - Gx * vet_x[0]  - sum(Gd*sensor_ref[0]);
    vet_u[0]= -Gi * sum(c*vet_x[1] - sensor_ref[1]) - Gx * vet_x[1]  - sum(Gd*sensor_ref[1]);
    vet_u[0]= -Gi * sum(c*vet_x[2] - sensor_ref[2]) - Gx * vet_x[2]  - sum(Gd*sensor_ref[2]);


    // achar next x
    double next_x;
    next_x = matrix_A * vet_x  - L * (value_sensor - c * vet_x) + b * vet_u;
    

    return 0;
}