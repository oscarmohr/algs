# DynamicArray

A dynamic array is an array that can grow dynamically to arbitrary sizes.

It achieves that by resizing if needed.

Underlying the dynamic array is a static array, which gets copied to a bigger array if a resize happens.

The resizing is a copying of the current array to an array of twice the current size.
