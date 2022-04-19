class Maths {
    static smoothInterpolation(bottomLeft, topLeft, bottomRight, topRight,
        xMin, xMax,
        zMin, zMax,
        x, z) {
            const width = xMax - xMin;
            const height = zMax - zMin;
            const xValue = 1 - (x - xMin) / width;
            const zValue = 1 - (z - zMin) / height;

            const a = this.smoothstep(bottomLeft, bottomRight, xValue);
            const b = this.smoothstep(topLeft, topRight, xValue);

            return this.smoothstep(a, b, zValue);
        }

    static smoothstep(edge0, edge1, x) {
        x = x * x * (3 - 2 * x);

        return (edge0 * x) + (edge1 * (1 - x));
    }
}
