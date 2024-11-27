import os
from PIL import Image, ExifTags

def correct_image_orientation(image):
    try:
        for orientation in ExifTags.TAGS.keys():
            if ExifTags.TAGS[orientation] == 'Orientation':
                break
        exif = image._getexif()
        if exif is not None:
            orientation = exif.get(orientation, 1)
            if orientation == 3:
                image = image.rotate(180, expand=True)
            elif orientation == 6:
                image = image.rotate(270, expand=True)
            elif orientation == 8:
                image = image.rotate(90, expand=True)
    except (AttributeError, KeyError, IndexError):
        # cases: image don't have getexif
        pass
    return image

def display_result(query_image, results):
    images = []
    for filename in results:
        img = Image.open(filename)
        img = correct_image_orientation(img)
        img = img.resize((150, 150))
        images.append(img)

    width = 150 * 5
    height = 150 * 2
    concatenated_image = Image.new("RGB", (width, height))

    for idx, img in enumerate(images):
        x = idx % 5
        y = idx // 5
        concatenated_image.paste(img, (x * 150, y * 150))

    # resultsディレクトリを作成
    save_path = os.path.join(os.path.dirname(__file__), "../results")
    os.makedirs(save_path, exist_ok=True)

    # query_imageのファイル名を取得
    query_image_filename = os.path.basename(query_image)
    query_image_name, _ = os.path.splitext(query_image_filename)

    # query_imageを保存
    query_img = Image.open(query_image)
    query_img = correct_image_orientation(query_img)
    query_img = query_img.resize((150, 150))
    query_image_save_path = os.path.join(save_path, f"query_{query_image_name}.jpeg")
    query_img.save(query_image_save_path)

    # 結果画像の保存
    results_image_save_path = os.path.join(save_path, f"result_{query_image_name}.jpeg")
    concatenated_image.save(results_image_save_path)