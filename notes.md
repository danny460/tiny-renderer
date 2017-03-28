# Learning Notes

### Point in triangle test
- Sum of Angles
- Same Side Technique
- Line Sweeping
- Barycentric Technique
    Executes faster, with a little more math involved. As three points of the triangle define a plane in the space, we'll need the basis vectors so we can give coordinate values to all points on the plane.

    > **Basis Vector**:  a set of vectors in a vector space V is called a basis, or a set of basis vectors, if the vectors are linearly independent and every vector in the vector space is a linear combination of this set.

    For a triangle defined by point t0, t1, t2, any point P on the plane can be described by:
    
            P = t2 + u * (t0 - t2) + v * (t1 - t2)

    For the above equation, note that if either *u < 0* or *v < 0* will yield a point P outside of the triangle. In addition, if *u + v > 1*, the point P will cross the line defined by t1, t0, and ended up outside the triangle.

    Now the problem becomes how to find the values of *u* and *v*, we'll need to transform the above equation:

            P - t2 = u * (t0 - t2) + v * (t1 - t2)
                v2 = u * v0 + v * v1

       dot(v2, v0) = dot(u * v0 + v * v1, v0)
       dot(v2, v1) = dot(u * v0 + v * v1, v1)

            
