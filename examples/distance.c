/*
 * Copyright 2017 Uber Technologies, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * Example program that calculates the distance in kilometers between two
 * hexagon indices.
 */

// mean Earth radius
#define R 6371.0088

#include <h3/h3api.h>
#include <math.h>
#include <stdio.h>

double dist(double th1, double ph1, double th2, double ph2) {
    double dx, dy, dz;
    ph1 -= ph2;

    dz = sin(th1) - sin(th2);
    dx = cos(ph1) * cos(th1) - cos(th2);
    dy = sin(ph1) * cos(th1);
    return asin(sqrt(dx * dx + dy * dy + dz * dz) / 2) * 2 * R;
}

int main(int argc, char *argv[]) {
    // 1455 Market St @ resolution 15
    H3Index h3HQ1 = stringToH3("8f2830828052d25");
    // 555 Market St @ resolution 15
    H3Index h3HQ2 = stringToH3("8f283082a30e623");

    double distance = 0;

    GeoCoord geoHQ1, geoHQ2;
    h3ToGeo(h3HQ1, &geoHQ1);
    h3ToGeo(h3HQ2, &geoHQ2);

    printf(
        "origin: (%lf, %lf)\n"
        "destination: (%lf, %lf)\n"
        "distance: %lfkm\n",
        radsToDegs(geoHQ1.lat), radsToDegs(geoHQ1.lon), radsToDegs(geoHQ2.lat),
        radsToDegs(geoHQ2.lon),
        dist(geoHQ1.lat, geoHQ1.lon, geoHQ2.lat, geoHQ2.lon));
    // Output:
    // origin: (37.775236, 237.580245)
    // destination: (37.789991, 237.597879)
    // distance: 2.256850km
}
