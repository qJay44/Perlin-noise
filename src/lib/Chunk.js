class Chunk {
    constructor(position) {
        this.pixels = new Array(CHUNK_SIZE * CHUNK_SIZE);
        this.mesh = new Mesh(position);
        this.isLoaded = false;
        this.isBuffered = false;
        this.position = position;
    }

    load(generator) {
        if (!this.isLoaded) {
            generator.generate(this);
            this.isLoaded = true;
        }
    }
    
    setPixel(x, z, type, heightMap = 1) {
        const chunk = z * CHUNK_SIZE + x;
        if (!this.pixels[chunk]) {
            this.pixels[chunk] = new Pixel();
        }
        this.pixels[chunk].type = type;
        this.pixels[chunk].heightMap = heightMap;
    }

    draw(renderer) {
        if (this.isBuffered) {
            renderer.drawChunk(this);
        }
    }

    addToBuffer() {
        if (!this.isBuffered) {
            this.mesh.add(this.pixels);
            this.isBuffered = true;
            
            return true;
        }

        return false;
    }
}