from PIL import Image

def create_multi_layer_ico(input_png_path, output_ico_path, icon_sizes=(256, 128, 64, 48, 32, 16)):
    # Load the original PNG image
    image = Image.open(input_png_path)

    # Create a list to hold the icon images
    icon_images = []

    # Generate the different sizes for the icon
    for size in icon_sizes:
        # Resize the image to the current size using the LANCZOS resampling algorithm
        icon_image = image.resize((size, size), Image.Resampling.LANCZOS)
        icon_images.append(icon_image)

    # Save the icon images as a single ICO file
    icon_images[0].save(output_ico_path, format='ICO', sizes=[(img.width, img.height) for img in icon_images])

# Usage
create_multi_layer_ico('Icon.png', 'Icon.ico')
