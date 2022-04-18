const chunk = document.getElementById('chunk');
const ctx = chunk.getContext('2d');
const title = 'Noise map - Simulator';

ctx.canvas.width = WINDOW_WIDTH;
ctx.canvas.height = WINDOW_HEIGHT;

const seed = Math.random() * 10000;
const noiseGenerator = new NoiseGenerator(seed);

const camera = new Camera({x: 50000, z: 50000});
const renderer = new Renderer();
const app = new Application(title, renderer, noiseGenerator);

app.loadEvents();
app.runLoop();
