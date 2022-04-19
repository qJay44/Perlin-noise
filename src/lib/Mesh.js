class Mesh {
    constructor(position) {
        this.position = position;
        // CHUNK_SIZE times 2 == 2D
        this.imgData = ctx.createImageData(CHUNK_SIZE, CHUNK_SIZE);
        this.data = this.imgData.data;
    }
    
    add(pixels) {
        const length = this.data.length;
        // Each pixel in the image data contains four elements: r, g, b, a
        for (let i = 0; i < length; i += 4) {
            const pixel = pixels[i / 4];
            let rgb = null;
            // defining different colors for each tupe of pixel
            if (pixel.type == PixelType.Water) {
                rgb = [3, 169, 244];
            } else if (pixel.type == PixelType.Grass) {
                rgb = [64, 154, 67];
            } else if (pixel.type == PixelType.Sand) {
                rgb = [255, 193, 7];
            } else if (pixel.type == PixelType.Dirt) {
                rgb = [74, 48, 39];
            } else {
                rgb = [249, 249, 249];
            }

            const bias = this.bias(pixel.heightMap);
            this.data[i + 0] = rgb[0] * bias;
            this.data[i + 1] = rgb[1] * bias;
            this.data[i + 2] = rgb[2] * bias;
            this.data[i + 3] = 255;
        }
    }

    // adding shadows to the pixels
    bias(heightMap) {
        const dark = 0.75;
        const light = 1;

        return dark * heightMap + light * (1 - heightMap);
    }
}
