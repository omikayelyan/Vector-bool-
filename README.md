# Vector_bool

The vector<bool> class is a partial specialization of vector for elements of type bool. It has an allocator for the underlying type that's used by the specialization, which provides space optimization by storing one bool value per bit.


A class that acts as a proxy to simulate bool& behavior, and whose objects can provide references to elements (single bits) within a vector<bool> object.
