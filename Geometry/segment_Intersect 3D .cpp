#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPS = 1e-9;

struct P {
    double x, y, z;
};

// Vector subtraction - stays consistent with your style
P vec3d(const P &a, const P &b) {
    return {b.x - a.x, b.y - a.y, b.z - a.z};
}

// 3D Cross Product - returns a vector in 3D
P cross(P A, P B) {
    return {
        A.y * B.z - A.z * B.y,
        A.z * B.x - A.x * B.z,
        A.x * B.y - A.y * B.x
    };
}

// Dot Product - essential for 3D comparisons
double dot(P A, P B) {
    return A.x * B.x + A.y * B.y + A.z * B.z;
}

// Magnitude squared - faster than using sqrt until the very end
double magSq(P A) {
    return dot(A, A);
}

// 3D Bounding Box check - your onSegment logic with Z-axis added
bool onSegment(const P &a, const P &b, const P &p) {
    return p.x >= min(a.x, b.x) - EPS && p.x <= max(a.x, b.x) + EPS &&
           p.y >= min(a.y, b.y) - EPS && p.y <= max(a.y, b.y) + EPS &&
           p.z >= min(a.z, b.z) - EPS && p.z <= max(a.z, b.z) + EPS;
}

// getIntersectionPoint - Uses the Dot Product ratio (your suggested improvement)
P getIntersectionPoint(P a, P b, P c, P d) {
    P AB = vec3d(a, b);
    P CD = vec3d(c, d);
    P AC = vec3d(a, c);
    
    P cp1 = cross(AC, CD);
    P cp2 = cross(AB, CD);
    
    // t = (cp1 . cp2) / |cp2|^2 
    // This is the correct way to get the signed scalar ratio in 3D
    double t = dot(cp1, cp2) / dot(cp2, cp2);
    
    return {a.x + t * AB.x, a.y + t * AB.y, a.z + t * AB.z};
}

bool segmentIntersect(const P &a, const P &b, const P &c, const P &d) {
    P AB = vec3d(a, b);
    P CD = vec3d(c, d);
    P AC = vec3d(a, c);

    P cp = cross(AB, CD);
    double cp_mag2 = magSq(cp);

    // Case 1: Parallel or Collinear Lines
    if (cp_mag2 < 1e-18) {
        // Check if they lie on the same infinite line by checking if AC is parallel to AB
        if (magSq(cross(AC, AB)) > 1e-18) return false; 
        
        // If they are on the same line, check if they overlap
        return onSegment(a, b, c) || onSegment(a, b, d) || 
               onSegment(c, d, a) || onSegment(c, d, b);
    }

    // Case 2: Skew Lines Check (Coplanarity)
    // In 3D, lines must be in the same plane to intersect.
    // The volume of the parallelepiped formed by AC, AB, and CD must be 0.
    if (abs(dot(AC, cp)) > EPS) return false; 

    // Case 3: Calculate point and check if it is within both segments
    P intersect = getIntersectionPoint(a, b, c, d);
    return onSegment(a, b, intersect) && onSegment(c, d, intersect);
}

void solve() {
    P a, b, c, d;
    // Reading 4 points, each with x, y, z
    if (!(cin >> a.x >> a.y >> a.z >> b.x >> b.y >> b.z 
              >> c.x >> c.y >> c.z >> d.x >> d.y >> d.z)) return;

    if (segmentIntersect(a, b, c, d)) {
        cout << "YES" << endl;
        
        P AB = vec3d(a, b);
        P CD = vec3d(c, d);
        
        if (magSq(cross(AB, CD)) < 1e-18) {
            cout << "Segments are collinear and overlapping." << endl;
        } else {
            P res = getIntersectionPoint(a, b, c, d);
            cout << fixed << setprecision(10) << "Point: " 
                 << res.x << " " << res.y << " " << res.z << endl;
        }
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    solve();
    return 0;
}