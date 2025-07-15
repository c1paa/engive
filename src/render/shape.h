// #include <vector>
// #include <string>
//
// using namespace std;
//
// class Shape {
// public:
//
//     vector<Point> vertices;
//     string texturePath;
//
//     Shape() {
//         vertices = vector<Point>();
//     }
//
//     Shape(vector<Point> vertices_) {
//         vertices = vertices_;
//     }
//
//     void AddPoint(Point& point) {
//         vertices.push_back(point);
//     }
//
//     void DeletePoint(Point& point) {
//         vertices.erase(find(vertices.begin(), vertices.end(), point));
//     }
//
//     void AddTexture() {
//
//     }
//
//     Shape Copy() const {
//         return {vertices};
//     }
//
// };